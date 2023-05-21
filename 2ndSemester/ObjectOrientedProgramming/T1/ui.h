//
// Created by Alen on 06/04/2022.
//

#pragma once
#include <utility>

#include "repo.h"
#include "service.h"
#include <iostream>
#include <cstring>

class UserInterface {

private:
    Service bill_service;

    void ui_remove();
    void ui_list();
    void ui_calculate();
    void ui_sort();

public:
    explicit UserInterface(Service bill_service) : bill_service(std::move(bill_service)) {};
    void ui_run();
};