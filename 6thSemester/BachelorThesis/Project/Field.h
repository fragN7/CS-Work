//
// Created by Alen on 25/04/2024.
//

#pragma once

#include <unordered_map>
#include <string>

class Field{
private:
    std::unordered_map<std::string, std::string> fields;

public:
    void addField(const std::string& key, const std::string& value);
    std::string getField(const std::string& key);
    void printAllFields();
};
