#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <map>
#include <random>

struct Product {
    int quantity;
    double unitPrice;
};

struct Bill {
    std::map<std::string, int> items; // Product name -> Quantity
    double totalPrice;
};

struct SupermarketInventory {
    std::map<std::string, Product> products;
    double money;
    std::vector<Bill> sales;
    std::mutex inventoryMutex;
    std::mutex moneyMutex;
    std::mutex salesMutex;
};

void sellProduct(SupermarketInventory& inventory, const std::string& productName, int quantity) {
    std::lock_guard<std::mutex> lock(inventory.inventoryMutex);
    if (inventory.products.find(productName) != inventory.products.end() && inventory.products[productName].quantity >= quantity) {
        std::lock_guard<std::mutex> lock2(inventory.moneyMutex);
        std::lock_guard<std::mutex> lock3(inventory.salesMutex);
        double totalPrice = inventory.products[productName].unitPrice * quantity;
        inventory.products[productName].quantity -= quantity;
        inventory.money += totalPrice;
        Bill bill;
        bill.items[productName] = quantity;
        bill.totalPrice = totalPrice;
        inventory.sales.push_back(bill);
    }
}

void inventoryCheck(const SupermarketInventory& inventory) {
    std::lock_guard<std::mutex> lock(inventory.inventoryMutex);
    std::lock_guard<std::mutex> lock2(inventory.moneyMutex);
    std::lock_guard<std::mutex> lock3(inventory.salesMutex);
    double totalMoney = 0;
    for (const auto& bill : inventory.sales) {
        for (const auto& item : bill.items) {
            totalMoney += inventory.products.at(item.first).unitPrice * item.second;
            if (inventory.products.find(item.first) != inventory.products.end()) {
                inventory.products.at(item.first).quantity -= item.second;
            }
        }
    }
    if (totalMoney == inventory.money) {
        std::cout << "Inventory check passed." << std::endl;
    } else {
        std::cout << "Inventory check failed." << std::endl;
    }
}

int main() {
    SupermarketInventory inventory;
    inventory.products["Bread"] = {100, 2.5};
    inventory.products["Milk"] = {50, 3.0};
    inventory.products["Eggs"] = {30, 1.0};

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&inventory]() {
            sellProduct(inventory, "Bread", 2);
            sellProduct(inventory, "Milk", 1);
            sellProduct(inventory, "Eggs", 3);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    inventoryCheck(inventory);

    return 0;
}
