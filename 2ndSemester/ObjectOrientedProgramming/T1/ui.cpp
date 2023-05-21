//
// Created by Alen on 06/04/2022.
//

#include <algorithm>
#include "ui.h"


void UserInterface::ui_remove() {

    char serial_number[41];
    std::cout << "Enter a serial number:\n";
    scanf("%41s", serial_number);
    try{
        this->bill_service.remove_bill(serial_number);
        std::cout << "Bill was removed\n";
    }
    catch (std::exception &exception) {
        std::cout << "Bill was not removed\n";
    }
}

void UserInterface::ui_list() {

    std::vector<Bill> bills = this->bill_service.get_all_bills();
    for(auto & bill : bills)
        std::cout << bill;
}

/// Get all the bills, iterate through them and check if it is a unpaid bill
void UserInterface::ui_calculate() {

    double sum = 0;
    std::vector<Bill> bills = this->bill_service.get_all_bills();
    for(auto & bill : bills)
        if(!bill.get_is_paid())
            sum = sum + bill.get_sum();

    std::cout << "The total sum is " << sum << "\n";
}

void UserInterface::ui_sort() {

    std::vector<Bill> bills = this->bill_service.get_all_bills();
    //std::sort(bills.begin(), bills.end(), Service::compare_dates());
}


void UserInterface::ui_run() {

    this->bill_service.populate_array();
    char command[41];
    while(true)
    {
        std::cout << "Enter a command:\n";
        scanf("%41s", command);

        if(!(strcmp(command, "remove")))
        {
            command[0] = '\0';
            this->ui_remove();
        }
        else if (!(strcmp(command, "list")))
        {
            command[0] = '\0';
            this->ui_list();
        }
        else if (!(strcmp(command, "calculate")))
        {
            command[0] = '\0';
            this->ui_calculate();
        }
        else if (!(strcmp(command, "sort")))
        {
            command[0] = '\0';
            this->ui_sort();
        }
        else if (!(strcmp(command, "exit")))
        {
            command[0] = '\0';
            return;
        }
        else {
            command[0] = '\0';
            std::cout << "Invalid command\n";
        }
    }
}