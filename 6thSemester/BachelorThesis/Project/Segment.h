//
// Created by Alen on 22/04/2024.
//

#pragma once


#include <string>
#include <utility>
#include <vector>

class Segment {

private:
    std::string segment;
    char terminator;

public:
    Segment(std::string segment, char terminator) : segment(std::move(segment)), terminator(terminator) {}
    ~Segment() = default;

    std::vector<std::string> parseSegment();
};
