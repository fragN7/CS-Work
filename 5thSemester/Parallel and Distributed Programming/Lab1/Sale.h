//
// Created by Alen on 22/10/2023.
//

#pragma once

#include "Inventory.h"

class Sale{

public:
    Inventory* inventory;
    Inventory* inventorySet;
    double profit;
    std::mutex lock;

    explicit Sale(Inventory* inventory, Inventory* inventorySet){
        this->inventory = inventory;
        this->inventorySet = inventorySet;
        this->profit = 0;
    }

    void sellProduct(Product* product){
        int quantity = this->inventory->getQuantityOfProduct(product);
        this->inventory->remove(product, quantity);
        this->profit += product->price * quantity;
    }

    double getProfit() const {
        return this->profit;
    }

    void start(){
        for(const auto &item: this->inventorySet->getProducts()){
            this->sellProduct(item);
        }
    }

};
