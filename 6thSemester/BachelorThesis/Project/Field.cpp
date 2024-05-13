//
// Created by Alen on 21/04/2024.
//

#include <iostream>
#include "Field.h"

void Field::addField(const std::string &key, const std::string &value) {
    this->fields[key] = value;
}

std::string Field::getField(const std::string &key) {
    return this->fields[key];
}

void Field::printAllFields() {
    for(const auto& pair : this->fields)
        std::cout << pair.first << "->  " << pair.second << std::endl;
}
