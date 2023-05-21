//
// Created by Alen on 04/05/2022.
//

#pragma once
#include <string>

class Dwelling {

private:
    double price{};
    bool is_profitable{};

public:
    Dwelling(double price, bool is_profitable);
    ~Dwelling() = default;
    std::string to_string() const;
    double get_price() const;
};