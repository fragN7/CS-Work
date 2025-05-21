// File: src/main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include <nlohmann/json.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxslt/transform.h>

// Helper to read a whole file into a string
std::string readFile(const std::string &path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Cannot open file: " + path);
    std::ostringstream contents;
    contents << in.rdbuf();
    return contents.str();
}

// Split a string by a single character delimiter
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::string item;
    std::stringstream ss(s);
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// Trim whitespace/newlines from ends of a string
std::string trim(const std::string &s) {
    size_t start = 0, end = s.size();
    while (start < end && (s[start]==' '||s[start]=='\t' || s[start]=='\r' || s[start]=='\n')) start++;
    while (end > start && (s[end-1]==' '||s[end-1]=='\t' || s[end-1]=='\r' || s[end-1]=='\n')) end--;
    return s.substr(start, end-start);
}

// Global variables to store delimiters and flags
char x12ElemDel = '*', x12CompDel = ':', x12SegTerm = '~';
char ediElemDel = '+', ediCompDel = ':', ediSegTerm = '\'';
bool hasUNA = false;
std::string unaStr;

// Parse ANSI X12 EDI into an XML DOM
void parseX12(const std::string &edi, xmlDocPtr doc, xmlNodePtr root) {
    // Determine delimiters from the ISA segment
    if (edi.rfind("ISA", 0) == 0) {
        x12ElemDel = edi[3];
        // Assume fixed length ISA: the component element separator is char at pos 104, seg term at 105
        std::string isa = edi.substr(0, edi.find(x12SegTerm));
        if (isa.size() >= 106) {
            x12CompDel = isa[104];
            x12SegTerm = isa[105];
        }
    }
    // Remove CR/LF for consistency
    std::string data = edi;
    data.erase(std::remove(data.begin(), data.end(), '\r'), data.end());
    // Split into segments by segment terminator
    auto segments = split(data, x12SegTerm);
    for (auto &segRaw : segments) {
        std::string seg = trim(segRaw);
        if (seg.empty()) continue;
        // Find segment ID (before first element separator)
        size_t pos = seg.find(x12ElemDel);
        std::string segId = (pos==std::string::npos ? seg : seg.substr(0,pos));
        std::string rest = (pos==std::string::npos ? "" : seg.substr(pos+1));
        xmlNodePtr segNode = xmlNewChild(root, NULL, BAD_CAST segId.c_str(), NULL);
        // Split the rest into elements
        auto elems = split(rest, x12ElemDel);
        for (size_t i = 0; i < elems.size(); ++i) {
            // Tag each element as SEGID_nn (e.g. ISA_01, ISA_02, etc.)
            char buf[10];
            snprintf(buf, 10, "%02zu", i+1);
            std::string tag = segId + "_" + buf;
            xmlNewChild(segNode, NULL, BAD_CAST tag.c_str(), BAD_CAST elems[i].c_str());
        }
    }
}

// Parse EDIFACT EDI into an XML DOM
void parseEDIFACT(const std::string &edi, xmlDocPtr doc, xmlNodePtr root) {
    std::string data = edi;
    // Check for UNA segment at start
    if (data.rfind("UNA", 0) == 0) {
        hasUNA = true;
        unaStr = data.substr(0, 9); // "UNAxxxxxx"
        if (unaStr.size() >= 9) {
            ediCompDel = unaStr[3];
            ediElemDel = unaStr[4];
            // unaStr[5]=decimal, [6]=release, [7]=reserved
            ediSegTerm = unaStr[8];
        }
        // Remove UNA from data
        data = data.substr(9);
    }
    // Split into segments by segment terminator
    auto segments = split(data, ediSegTerm);
    for (auto &segRaw : segments) {
        std::string seg = trim(segRaw);
        if (seg.empty()) continue;
        size_t pos = seg.find(ediElemDel);
        std::string segId = (pos==std::string::npos ? seg : seg.substr(0,pos));
        std::string rest = (pos==std::string::npos ? "" : seg.substr(pos+1));
        xmlNodePtr segNode = xmlNewChild(root, NULL, BAD_CAST segId.c_str(), NULL);
        auto elems = split(rest, ediElemDel);
        for (size_t i = 0; i < elems.size(); ++i) {
            std::string val = elems[i];
            // Do not split composites for simplicity; keep as single element
            std::string tag = segId + "_" + std::to_string(i+1);
            xmlNewChild(segNode, NULL, BAD_CAST tag.c_str(), BAD_CAST val.c_str());
        }
    }
}

// Parse VDA EDI (fixed-width) into XML
void parseVDA(const std::string &edi, xmlDocPtr doc, xmlNodePtr root) {
    std::istringstream iss(edi);
    std::string line;
    while (std::getline(iss, line)) {
        line = trim(line);
        if (line.empty()) continue;
        // Assume first token or first 3 chars is segment ID
        std::string segId;
        if (line.size() >= 3) {
            segId = line.substr(0, 3);
        } else {
            segId = line;
        }
        xmlNodePtr segNode = xmlNewChild(root, NULL, BAD_CAST segId.c_str(), NULL);
        std::string rest = "";
        if (line.size() > 3) {
            rest = trim(line.substr(3));
        }
        // Store the rest of the line in one child element
        std::string tag = segId + "_DATA";
        xmlNewChild(segNode, NULL, BAD_CAST tag.c_str(), BAD_CAST rest.c_str());
    }
}

// Convert XML back to X12 EDI
std::string xmlToX12(xmlDocPtr doc) {
    std::string out;
    xmlNodePtr root = xmlDocGetRootElement(doc);
    for (xmlNodePtr seg = root->children; seg; seg = seg->next) {
        if (seg->type != XML_ELEMENT_NODE) continue;
        std::string segId = (const char*)seg->name;
        std::vector<std::string> elems;
        for (xmlNodePtr child = seg->children; child; child = child->next) {
            if (child->type == XML_ELEMENT_NODE) {
                xmlChar* content = xmlNodeGetContent(child);
                elems.push_back((content ? (const char*)content : std::string("")));
                xmlFree(content);
            }
        }
        // Rebuild segment string
        std::string line = segId;
        for (size_t i = 0; i < elems.size(); ++i) {
            std::string val = elems[i];
            // Pad ISA fields to fixed lengths (ISA01=2, ISA02=10, ISA03=2, ISA04=10, ISA05=2, ISA06=15, ISA07=2, ISA08=15, ISA09=6, ISA10=4, ISA11=1, ISA12=5, ISA13=9, ISA14=1, ISA15=1, ISA16=1)
            if (segId == "ISA") {
                const int isaLens[16] = {2,10,2,10,2,15,2,15,6,4,1,5,9,1,1,1};
                if (i < 16) {
                    if ((int)val.size() < isaLens[i]) {
                        val += std::string(isaLens[i] - val.size(), ' ');
                    }
                }
            }
            line += x12ElemDel;
            line += val;
        }
        line += x12SegTerm;
        out += line + "\n";
    }
    return out;
}

// Convert XML back to EDIFACT EDI
std::string xmlToEDIFACT(xmlDocPtr doc) {
    std::string out;
    // If there was a UNA, emit it (ensure it ends with the segment terminator)
    if (hasUNA) {
        std::string una = unaStr;
        if (una.back() != ediSegTerm) una += ediSegTerm;
        out += una + "\n";
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);
    for (xmlNodePtr seg = root->children; seg; seg = seg->next) {
        if (seg->type != XML_ELEMENT_NODE) continue;
        std::string segId = (const char*)seg->name;
        std::vector<std::string> elems;
        for (xmlNodePtr child = seg->children; child; child = child->next) {
            if (child->type == XML_ELEMENT_NODE) {
                xmlChar* content = xmlNodeGetContent(child);
                elems.push_back((content ? (const char*)content : std::string("")));
                xmlFree(content);
            }
        }
        std::string line = segId;
        for (auto &val : elems) {
            line += ediElemDel;
            line += val;
        }
        line += ediSegTerm;
        out += line + "\n";
    }
    return out;
}

// Convert XML back to VDA EDI (simple concatenation)
std::string xmlToVDA(xmlDocPtr doc) {
    std::string out;
    xmlNodePtr root = xmlDocGetRootElement(doc);
    for (xmlNodePtr seg = root->children; seg; seg = seg->next) {
        if (seg->type != XML_ELEMENT_NODE) continue;
        std::string segId = (const char*)seg->name;
        std::string data = "";
        if (seg->children && seg->children->type == XML_ELEMENT_NODE) {
            xmlChar* content = xmlNodeGetContent(seg->children);
            data = (content ? (const char*)content : std::string(""));
            xmlFree(content);
        }
        std::string line = segId;
        if (!data.empty()) {
            // Insert a space or fixed padding as needed
            line += " " + data;
        }
        out += line + "\n";
    }
    return out;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input.edi> <transform.xsl> <config.json>\n";
        return 1;
    }
    try {
        std::string ediPath = argv[1];
        std::string xslPath = argv[2];
        std::string configPath = argv[3];

        // Load files
        std::string ediData = readFile(ediPath);
        std::string configData = readFile(configPath);
        nlohmann::json config = nlohmann::json::parse(configData);

        // Extract config fields
        std::string ediStandard = config.value("EDI Standard", "");
        std::string sender = config.value("Sender Partner", "");
        std::string receiver = config.value("Receiver Partner", "");
        std::string objectType = config.value("Object Type", "");
        std::string password = config.value("Password", "");

        // Initialize libxml and libxslt
        xmlInitParser();
        LIBXML_TEST_VERSION
        xsltInit();

        // Create XML document for the EDI
        xmlDocPtr xmlDoc = xmlNewDoc(BAD_CAST "1.0");
        xmlNodePtr root = xmlNewNode(NULL, BAD_CAST "EDI");
        xmlDocSetRootElement(xmlDoc, root);

        // Parse EDI into XML based on format
        if (ediStandard == "ANSI X12" || (!ediStandard.size() && ediData.rfind("ISA",0)==0)) {
            parseX12(ediData, xmlDoc, root);
        } else if (ediStandard == "EDIFACT" || (!ediStandard.size() && 
                  (ediData.rfind("UNA",0)==0 || ediData.rfind("UNB",0)==0))) {
            parseEDIFACT(ediData, xmlDoc, root);
        } else { 
            parseVDA(ediData, xmlDoc, root);
        }

        // Load XSLT stylesheet
        xsltStylesheetPtr xsl = xsltParseStylesheetFile((const xmlChar*)xslPath.c_str());
        if (!xsl) {
            std::cerr << "Error: Cannot parse XSL file.\n";
            return 1;
        }
        // Prepare parameters for the XSLT (name-value pairs, null-terminated)
        std::vector<const char*> params = {
            "SenderPartner", sender.c_str(),
            "ReceiverPartner", receiver.c_str(),
            "ObjectType", objectType.c_str(),
            NULL
        };
        // Apply transformation
        xmlDocPtr resDoc = xsltApplyStylesheet(xsl, xmlDoc, params.data());
        if (!resDoc) {
            std::cerr << "Error: XSLT transformation failed.\n";
            return 1;
        }

        // Convert back to EDI
        std::string outputEdi;
        if (ediStandard == "ANSI X12" || (!ediStandard.size() && ediData.rfind("ISA",0)==0)) {
            outputEdi = xmlToX12(resDoc);
        } else if (ediStandard == "EDIFACT" || (!ediStandard.size() && 
                     (ediData.rfind("UNA",0)==0 || ediData.rfind("UNB",0)==0))) {
            outputEdi = xmlToEDIFACT(resDoc);
        } else {
            outputEdi = xmlToVDA(resDoc);
        }

        // Output the result (to stdout; redirect or save as needed)
        std::cout << outputEdi;

        // Cleanup
        xsltFreeStylesheet(xsl);
        xmlFreeDoc(resDoc);
        xmlFreeDoc(xmlDoc);
        xsltCleanupGlobals();
        xmlCleanupParser();
    }
    catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
