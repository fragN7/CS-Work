//
// Created by Alen on 06/04/2022.
//

#include "repo.h"

unsigned long long Repo::find(const std::string& serial_number) {

    std::vector<Bill> bills = this->bill_repo;
    for(std::vector<Bill>::size_type i = 0; i != bills.size(); i++)
        if(bills[i].get_serial_number() == serial_number)
            return i;
    return -1;
}

void Repo::add(const Bill& bill) {

    this->bill_repo.push_back(bill);
}

void Repo::remove(const std::string& serial_number) {

    unsigned long long index = this->find(serial_number);
    if(index == -1)
        throw std::exception();
    this->bill_repo.erase(this->bill_repo.begin() + index);
}

std::vector<Bill> Repo::get_bills() {
    return this->bill_repo;
}
