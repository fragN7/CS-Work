//
// Created by Alen on 04/05/2022.
//

#include "dwelling.h"
#include <string>
#pragma once

class Client {

protected:
    std::string name;
    double income{};

public:

    Client(const std::string& name, double income);
    virtual ~Client() = default;
    virtual double total_income() = 0;
    virtual std::string to_string() = 0;
    virtual bool is_interested(Dwelling dwelling) = 0;

    std::string get_name();

};


