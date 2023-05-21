//
// Created by Alen on 06/04/2022.
//

#include "service.h"

void Service::remove_bill(const std::string& serial_number) {

    this->bill_repo.remove(serial_number);
}

std::vector<Bill> Service::get_all_bills() {
    return this->bill_repo.get_bills();
}


void Service::populate_array() {

    std::string serial_number = "0A33455X";
    std::string company = "nike";
    std::string date = "12/12/1222";
    double sum = 43;
    bool is_paid = false;

    Bill b = Bill(serial_number, company, date, sum, is_paid);
    this->bill_repo.add(b);

    std::string serial_number1 = "dskadoasd";
    std::string company1 = "nike";
    std::string date1 = "12/12/1222";
    double sum1 = 43;
    bool is_paid1 = false;

    Bill b1 = Bill(serial_number1, company1, date1, sum1, is_paid1);
    this->bill_repo.add(b1);

    std::string serial_number2 = "dskadlolopoasd";
    std::string company2 = "nike";
    std::string date2 = "12/12/1222";
    double sum2 = 43;
    bool is_paid2 = false;

    Bill b2 = Bill(serial_number2, company2, date2, sum2, is_paid2);
    this->bill_repo.add(b2);

    std::string serial_number3 = "dskadfddoasd";
    std::string company3 = "nike";
    std::string date3 = "12/12/1222";
    double sum3 = 43;
    bool is_paid3 = true;

    Bill b3 = Bill(serial_number3, company3, date3, sum3, is_paid3);
    this->bill_repo.add(b3);

    std::string serial_number4 = "dsasad";
    std::string company4 = "nike";
    std::string date4 = "12/12/1222";
    double sum4 = 43;
    bool is_paid4 = false;

    Bill b4 = Bill(serial_number4, company4, date4, sum4, is_paid4);
    this->bill_repo.add(b4);

}

bool Service::compare_dates(const std::string &date1, const std::string &date2) {

    if(date1 > date2)
        return true;
    return false;
}


