//
// Created by Alen on 16/03/2022.
//

#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <shellapi.h>
#include "../validation/validation.h"
#include "../service/service.h"
#include "../errors/exceptions.h"
#include "../repo/repository.h"
#pragma once


class UserInterface {

private:

    Event_Service event_service;
    Event_Service user_service;

    static void print_admin_menu();
    static void print_user_menu();

    void ui_add();
    void ui_delete();
    void ui_update();
    void ui_list();
    void ui_save(const std::string& file_name);
    void ui_read(const std::string& file_name);

    void ui_user_show_events();
    void ui_user_my_events();
    void ui_user_save(const std::string& file_name);

public:

    explicit UserInterface(Event_Service event_service, Event_Service user_service) : event_service(event_service), user_service(user_service) {};
    void run(const std::string& repo_type);

};