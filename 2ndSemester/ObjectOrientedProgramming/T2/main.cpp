//
// Created by Alen on 04/05/2022.
//

#include "service.h"
#include "ui.h"

int main() {

    Service service;
    UserInterface ui(service);
    ui.run_ui();
    return 0;
}
