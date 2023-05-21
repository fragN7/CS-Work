//
// Created by Alen on 04/05/2022.
//

#include "dwelling.h"
#include "client.h"
#include <vector>
#pragma once


class Service {

private:
    std::vector<Dwelling*> dwellings;
    std::vector<Client*> clients;

public:

    Service() = default;
    ~Service();

    void add_dwelling(Dwelling* dwelling);
    void remove_client(const std::string& name);
    std::vector<Client*> get_interested_clients(Dwelling dwelling);
    void file_write(const std::string& file_name);

    void populate_list();
    std::vector<Client*> get_all_clients();
    std::vector<Dwelling*> get_all_dwellings();

};
