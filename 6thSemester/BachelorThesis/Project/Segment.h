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
    std::string terminator;

public:
    explicit Segment(std::string segment, std::string terminator) : segment(std::move(segment)), terminator(std::move(terminator)) {}
    ~Segment() = default;

    std::vector<std::string> parseSegment();
};
