//
// Created by Alen on 06/07/2022.
//

#pragma once
#include "User.h"
#include <string>
#include <vector>


class Topic {

private:
    std::string topic_name;
    std::vector<User> users;

public:
    explicit Topic(std::string topic) {this->topic_name = std::move(topic);}
    Topic() = default;
    std::string get_topic() {return this->topic_name;}
};
