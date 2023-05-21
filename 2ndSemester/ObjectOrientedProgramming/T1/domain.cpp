//
// Created by Alen on 06/04/2022.
//

#include "domain.h"

Bill::Bill(std::string& serial_number, std::string& company, std::string& due_date, double sum, bool is_paid) {

    this->serial_number = serial_number;
    this->company = company;
    this->due_date = due_date;
    this->sum = sum;
    this->is_paid = is_paid;
}

std::string Bill::get_serial_number() {
    return this->serial_number;
}

std::string Bill::get_company() {
    return this->company;
}

std::string Bill::get_due_date() {
    return this->due_date;
}

double Bill::get_sum() const {
    return this->sum;
}

bool Bill::get_is_paid() const {
    return this->is_paid;
}

std::ostream &operator<<(std::ostream &output, Bill &bill) {
    output << bill.serial_number << " | " << bill.company << " | " << bill.due_date << " | " << bill.sum << " | " << bill.is_paid << "\n";
    return output;
}

