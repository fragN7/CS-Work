//
// Created by Alen on 04/05/2022.
//

#include <algorithm>
#include "service.h"
#include "person.h"
#include "company.h"
#include "dwelling.h"
#include <fstream>

void Service::add_dwelling(Dwelling* dwelling) {

    this->dwellings.push_back(dwelling);
}

void Service::remove_client(const std::string& name) {

    int i = 0;
    for(auto &client : this->clients)
    {
        if (client->get_name() == name)
        {
            this->clients.erase(this->clients.begin() + i);
            break;
        }
        i++;
    }
}

std::vector<Client *> Service::get_interested_clients(Dwelling dwelling) {

    std::vector<Client*> interested_clients;
    std::copy_if(this->clients.begin(), this->clients.end(), std::back_inserter(interested_clients), [&dwelling](auto the_client){return the_client->is_interested(dwelling);});
    return interested_clients;
}

void Service::file_write(const std::string& file_name) {

    std::ofstream file(file_name);
    for(auto &client : this->clients)
        file << client->to_string();
}

std::vector<Client *> Service::get_all_clients() {
    return this->clients;
}

std::vector<Dwelling *> Service::get_all_dwellings() {
    return this->dwellings;
}

void Service::populate_list() {

    auto a = new Person("mike", 321);
    this->clients.push_back(a);

    auto b = new Person("michael", 123);
    this->clients.push_back(b);

    auto c = new Company("company", 2312, 321);
    this->clients.push_back(c);

    auto d = new Company("some company", 232, 365);
    this->clients.push_back(d);

    auto e = new Dwelling(123, true);
    this->dwellings.push_back(e);
}

Service::~Service() {

    for(auto dwelling : this->dwellings)
        delete dwelling;

    for(auto client: this->clients)
        delete client;
}
