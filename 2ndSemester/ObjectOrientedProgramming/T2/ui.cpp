//
// Created by Alen on 04/05/2022.
//

#include "ui.h"

void UserInterface::ui_add_dwelling() {

    double price;
    std::cout << "Price:\n";
    std::cin >> price;

    bool interested;
    std::cout << "Is profitable:\n";
    std::cin >> interested;

    auto* dwelling = new Dwelling(price, interested);
    this->service.add_dwelling(dwelling);

    std::vector<Client*> interested_clients = this->service.get_interested_clients(*dwelling);
    for(auto& interested_client : interested_clients)
        std::cout << interested_client->to_string();
}

void UserInterface::ui_remove_client() {

    std::string name;
    std::cout << "Name:\n";
    std::cin >> name;

    this->service.remove_client(name);
}

void UserInterface::ui_list_all() {

    std::cout << "Clients:\n";
    std::vector<Client*> all_clients = this->service.get_all_clients();
    for(auto &client : all_clients)
        std::cout << client->to_string();

    std::cout << "Dwellings:\n";
    std::vector<Dwelling*> all_dwellings = this->service.get_all_dwellings();
    for(auto &dwelling : all_dwellings)
        std::cout << dwelling->to_string();
}

void UserInterface::print_menu() {

    std::cout << "'add' - add dwelling\n";
    std::cout << "'remove' - remove client\n";
    std::cout << "'list' - list all clients\n";
    std::cout << "'save' - save to file\n";
    std::cout << "'exit' - exit\n";
}

void UserInterface::save_file() {

    this->service.file_write(R"(C:\Users\Alen\Documents\GitHub\t2-913-Iaguta-Alen-Mihael-1\something.txt)");
}

void UserInterface::run_ui() {

    this->print_menu();
    this->service.populate_list();

    std::string command;
    while(true){

        std::cout << "Please enter your command here:\n";
        std::cin >> command;
        if(command == "add")
            this->ui_add_dwelling();
        else if(command == "remove")
            this->ui_remove_client();
        else if(command == "list")
            this->ui_list_all();
        else if(command == "save")
            this->save_file();
        else if(command == "exit")
            return;
        else
            std::cout << "Invalid command!\n";
    }
}

