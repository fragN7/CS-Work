//
// Created by Alen on 24/04/2024.
//

#pragma once


#include <string>
#include <utility>
#include <vector>

class Document {
private:
    std::string filename;
    std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string>>>> result;

public:
    explicit Document(std::string  filename) : filename(std::move(filename)) {}
    ~Document() = default;

    std::string loadFile();
    
};

