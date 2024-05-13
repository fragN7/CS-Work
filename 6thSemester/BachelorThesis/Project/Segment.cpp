//
// Created by Alen on 24/04/2024.
//

#include "Segment.h"

std::vector<std::string> Segment::parseSegment() {

    std::vector<std::string> fields;
    size_t start = 0;
    size_t end = this->segment.find(terminator);

    while(end != std::string::npos){
        fields.push_back(segment.substr(start, end - start));
        start = end + 1;
        end = segment.find(segment, terminator);
    }

    return fields;
}
