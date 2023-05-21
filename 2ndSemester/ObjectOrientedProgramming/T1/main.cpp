//
// Created by Alen on 06/04/2022.
//

#include "tests.h"
#include "repo.h"
#include "service.h"
#include "ui.h"
#include <iostream>

int main() {
    std::cout << "Started\n";

    Tests tests;
    //Tests::test_all();

    Repo bill_repo;
    Service bill_service(bill_repo);
    UserInterface user_interface(bill_service);

    user_interface.ui_run();

    std::cout << "Finished\n";
}