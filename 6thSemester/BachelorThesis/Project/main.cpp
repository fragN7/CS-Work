#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include "Document.h"

// Function to parse the message and populate the map
std::map<std::string, std::map<std::string, std::string>> parseMessage(const std::string& message) {
    std::map<std::string, std::map<std::string, std::string>> resultMap;
    std::istringstream iss(message);
    std::string line;

    // Iterate through each line of the message
    while (std::getline(iss, line, '\n')) {
        std::istringstream lineStream(line);
        std::string segment;
        std::vector<std::string> elements;

        // Split the line into segments separated by '*'
        while (std::getline(lineStream, segment, '*')) {
            elements.push_back(segment);
        }

        // If the line contains elements
        if (!elements.empty()) {
            std::string segmentType = elements[0]; // Get the segment type
            std::map<std::string, std::string> segmentMap;

            // Populate the segment map with element values
            for (size_t i = 1; i < elements.size(); ++i) {
                segmentMap[std::to_string(i)] = elements[i];
            }

            // Store the segment map in the resultMap
            resultMap[segmentType] = segmentMap;
        }
    }

    return resultMap;
}

int main() {
    std::string filename = R"(C:\Users\Alen\Documents\GithubPrivate\CS-Work\6thSemester\BachelorThesis\Project\test.tst)";
    Document file(filename);
    std::string result = file.loadFile();

    std::map<std::string, std::map<std::string, std::string>> resultMap = parseMessage(result);

    for (const auto& pair : resultMap) {
        std::cout << pair.first << ":" << std::endl;
        for (const auto& innerPair : pair.second) {
            std::cout << "    " << innerPair.first << ": " << innerPair.second << std::endl;
        }
    }

    return 0;
}
