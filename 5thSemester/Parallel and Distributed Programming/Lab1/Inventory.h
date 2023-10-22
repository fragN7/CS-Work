//
// Created by Alen on 22/10/2023.
//

#pragma once

#include <unordered_map>
#include <mutex>
#include <vector>
#include "Product.h"

class Inventory{

public:
    std::unordered_map<Product*, int> products;
    std::unordered_map<Product*, std::mutex*> mutexes;
    std::mutex lock;

    explicit Inventory() = default;

    std::vector<Product*> getProducts(){
        this->lock.lock();
        std::vector<Product*> keys;
        keys.reserve(products.size());

        for (auto & product : products) {
            keys.push_back(product.first);
        }

        Inventory::lock.unlock();

        return keys;
    }

    int getQuantityOfProduct(Product* product){
        this->mutexes[product]->lock();

        int quantity = 0;

        if(this->products.count(product) == 1){
            quantity = this->products[product];
        }

        this->mutexes[product]->unlock();

        return quantity;
    }

    bool containsProduct(Product* product){
        this->lock.lock();

        bool result = false;
        if(products.count(product) == 1)
            result = true;

        this->lock.unlock();

        return result;
    }

    double computeValue(){
        this->lock.lock();
        double totalPrice = 0;

        for(auto& product: products){
            totalPrice += product.first->price* product.second;
        }
    }

    void add(Product* product, int quantity){
        this->lock.lock();

        if(this->products.count(product) == 0){
            this->products[product] = quantity;
            this->mutexes[product] = new std::mutex();
        }

        this->lock.unlock();
    }

    void remove(Product* product, int quantity){
        this->mutexes[product]->lock();
        int prevQuantity = this->products[product];
        this->products[product] = prevQuantity - quantity;
        this->mutexes[product]->unlock();
    }

};
