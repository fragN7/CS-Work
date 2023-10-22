//
// Created by Alen on 22/10/2023.
//

#pragma once

#include <iostream>
#include "Inventory.h"
#include "Sale.h"

class Checker{

public:
    double initialValue;
    Inventory* inventory;
    std::vector<Sale*> sales;
    std::mutex lock;

    explicit Checker(double totalValue, Inventory* inventory, std::vector<Sale*> sales){
        this->initialValue = totalValue;
        this->inventory = inventory;
        this->sales = sales;
    }

    void checkInventory(double money){
        this->lock.lock();

        double totalSale = 0;
        for(auto& sale: sales){
            totalSale += sale->getProfit();
        }

        if(money >= totalSale){
            std::cout << "Inventory is ok" << std::endl;
        } else {
            std::cout << "Inventory is not ok" << std::endl;
        }

        this->lock.unlock();
    }
};
