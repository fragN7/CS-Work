//
// Created by Alen on 04/05/2022.
//

#pragma once

#include "service.h"
#include <iostream>
#pragma once

class UserInterface {

private:
    Service service;

    void ui_add_dwelling();
    void ui_remove_client();
    void ui_list_all();
    static void print_menu();
    void save_file();

public:
    explicit UserInterface(Service& service) : service(service){};
    ~UserInterface() = default;

    void run_ui();
};