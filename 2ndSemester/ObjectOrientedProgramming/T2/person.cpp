//
// Created by Alen on 04/05/2022.
//

#include "person.h"

Person::Person(const std::string &name, double income) : Client(name, income){

}

bool Person::is_interested(Dwelling dwelling) {

    if(dwelling.get_price()/1000 <= this->income)
        return true;
    return false;
}

double Person::total_income() {

    return this->income;
}

std::string Person::to_string() {
    return "Name:" + this->name + " Income:" + std::to_string(this->income) + "\n";
}
