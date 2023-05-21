//
// Created by Alen on 06/07/2022.
//

#pragma once
#include <string>
#include <utility>


class User {

private:
    std::string name;

public:
    explicit User(std::string name) {this->name = std::move(name);}
    User() = default;
    std::string get_name() {return this->name;}
};
