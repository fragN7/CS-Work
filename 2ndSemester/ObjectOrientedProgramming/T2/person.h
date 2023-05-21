//
// Created by Alen on 04/05/2022.
//

#include "client.h"
#pragma once

class Person : public Client {

public:
    Person(const std::string &name, double income);
    ~Person() override = default;
    double total_income() override;
    std::string to_string() override;
    bool is_interested(Dwelling dwelling) override;
};
