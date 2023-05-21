//
// Created by Alen on 06/04/2022.
//

#pragma once
#include <string>
#include <sstream>

class Bill {

private:
    std::string serial_number;
    std::string company;
    std::string due_date;
    double sum;
    bool is_paid;

public:
    Bill(std::string& serial_number, std::string& company, std::string& due_date, double sum, bool is_paid);
    ~Bill() = default;

    std::string get_serial_number();
    std::string get_company();
    std::string get_due_date();
    double get_sum() const;
    bool get_is_paid() const;

    friend std::ostream & operator<<(std::ostream& output, Bill& bill);

};