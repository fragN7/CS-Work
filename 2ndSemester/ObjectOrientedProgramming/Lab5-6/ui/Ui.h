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
#include "../array/Array.h"
#pragma once


class UserInterface {

private:

    Event_Service event_service;
    Event_Service user_event_service;

    void ui_add();
    void ui_delete();
    void ui_update();
    void ui_list();
    static void print_admin_menu();

    void ui_user_show_events();
    void ui_user_my_events();
    static void print_user_menu();

public:

    explicit UserInterface(Event_Service  event_service, Event_Service  user_event_service) : event_service(std::move(event_service)), user_event_service(std::move(user_event_service)) {};
    void run();

};
