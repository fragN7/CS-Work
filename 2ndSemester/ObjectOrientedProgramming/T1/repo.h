//
// Created by Alen on 06/04/2022.
//

#pragma once
#include "domain.h"
#include <vector>

class Repo {

private:
    std::vector<Bill> bill_repo;

public:
    Repo() = default;

    unsigned long long find(const std::string& serial_number);
    void add(const Bill& bill);

    /// Calls the find function which returns the index at the position it has been found, -1 if it didn't find the bill, throws exception
    /// \param serial_number Unique identifier
    void remove(const std::string& serial_number);
    std::vector<Bill> get_bills();
};
