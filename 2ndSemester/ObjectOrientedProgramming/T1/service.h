//
// Created by Alen on 06/04/2022.
//

#pragma once
#include "repo.h"

class Service{

private:
    Repo bill_repo;


public:
    explicit Service(Repo& bill_repo) : bill_repo(bill_repo) {};

    /// Calls the repo
    /// \param serial_number Unique identifier
    void remove_bill(const std::string& serial_number);
    std::vector<Bill> get_all_bills();
    static bool compare_dates(const std::string& date1, const std::string& date2);

    void populate_array();
};