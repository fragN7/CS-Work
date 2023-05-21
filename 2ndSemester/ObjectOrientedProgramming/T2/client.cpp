//
// Created by Alen on 04/05/2022.
//

#include "client.h"

Client::Client(const std::string& name, double income) {

    this->name = name;
    this->income = income;
}

std::string Client::get_name() {

    return this->name;
}
