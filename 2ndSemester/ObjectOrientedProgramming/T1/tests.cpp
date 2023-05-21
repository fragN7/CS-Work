//
// Created by Alen on 06/04/2022.
//

#include "tests.h"

void Tests::test_all() {

    Repo bill_repo;
    Service bill_service(bill_repo);

    std::string serial_number4 = "dsasad";
    std::string company4 = "nike";
    std::string date4 = "12/12/1222";
    double sum4 = 43;
    bool is_paid4 = false;

    Bill b4 = Bill(serial_number4, company4, date4, sum4, is_paid4);

    bill_repo.add(b4);
    //assert(!bill_repo.get_bills().empty());

    bill_service.remove_bill(serial_number4);
    //assert(bill_repo.get_bills().empty());
}
