//
// Created by Alen on 04/05/2022.
//

#include "dwelling.h"


Dwelling::Dwelling(double price, bool is_profitable) {

    this->price = price;
    this->is_profitable = is_profitable;
}

double Dwelling::get_price() const {
    return this->price;
}

std::string Dwelling::to_string() const {
    return "Price:" + std::to_string(this->price) + " Is profitable:" + std::to_string(this->is_profitable);
}
