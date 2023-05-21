//
// Created by Alen on 06/07/2022.
//

#pragma once
#include <string>
#include <utility>
#include "User.h"


class Post{

private:
    std::string id, text, timestamp;
    User post_user;

public:
    explicit Post(std::string id, std::string text, std::string timestamp, User post_user) {
        this->id = std::move(id);
        this->text = std::move(text);
        this->timestamp = std::move(timestamp);
        this->post_user = std::move(post_user);
    }
    Post() = default;
    std::string get_id() {return this->id;}
    std::string get_text() {return this->text;}
    std::string get_timestamp() {return this->timestamp;}
    User get_user() {return this->post_user;}
};
