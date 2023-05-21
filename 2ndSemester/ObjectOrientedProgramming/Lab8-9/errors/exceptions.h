//
// Created by Alen on 19/03/2022.
//

#pragma once
#include <exception>
#include <string>
#include <utility>


class RepoError : public std::exception {
    std::string message;
public:
    explicit RepoError(std::string message) :message(std::move(message)) {};
    std::string get_message() { return this->message; };
};

class ValidError : public std::exception {
    std::string message;
public:
    explicit ValidError(std::string message) :message(std::move(message)) {};
    std::string get_message() { return this->message; };
};

class UserError : public std::exception {
    std::string message;
public:
    explicit UserError(std::string message) :message(std::move(message)) {};
    std::string get_message() { return this->message; };
};
