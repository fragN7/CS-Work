//
// Created by Alen on 04/05/2022.
//

#include "client.h"
#pragma once

class Company : public Client {

private:
    double investments_money{};

public:
    Company(const std::string& name, double income, double investments_money);
    ~Company() override = default;
    double total_income() override;
    std::string to_string() override;
    bool is_interested(Dwelling dwelling) override;

};
