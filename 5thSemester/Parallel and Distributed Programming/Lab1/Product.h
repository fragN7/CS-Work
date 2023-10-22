//
// Created by Alen on 22/10/2023.
//

#include <string>

#pragma once

class Product {

public:
    std::string id;
    int price;

    explicit Product(): price{0}, id{""} {}
    Product(const std::string& id, int price) {
        this->id = id;
        this->price = price;
    }

    bool operator==(Product& p) const{
        return p.price == this->price && p.id == this->id;
    }
};
