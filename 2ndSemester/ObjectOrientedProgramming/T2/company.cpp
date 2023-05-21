//
// Created by Alen on 04/05/2022.
//

#include "company.h"

Company::Company(const std::string& name, double income, double investments_money) : Client(name, income){

    this->investments_money = investments_money;
}

double Company::total_income() {

    return this->income + this->investments_money;
}

std::string Company::to_string() {

    return "Name:" + this->name + " Income:" + std::to_string(this->income) + " Money from investments:" + std::to_string(this->investments_money) + "\n";
}

bool Company::is_interested(Dwelling dwelling) {

    if(dwelling.get_price()/100 <= this->total_income())
        return true;
    return false;
}
