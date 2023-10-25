#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <map>
#include <random>

struct Product {
    std::string name;
    double price;
    int quantity;

    Product(std::string n, double p, int q) : name(std::move(n)), price(p), quantity(q) {}
};

struct Bill {
    std::vector<std::pair<Product, int>> items;
    double totalPrice;
};

struct Inventory {

    std::vector<Product> products;
    double money{};
    std::vector<Bill> bills;

    std::mutex productsMutex;
    std::mutex moneyMutex;
    std::mutex billsMutex;

    void sell(std::vector<std::pair<Product, int>> items, double totalPrice) {
        std::lock_guard<std::mutex> lock(productsMutex);
        std::lock_guard<std::mutex> moneyLock(moneyMutex);
        std::lock_guard<std::mutex> billsLock(billsMutex);

        for (const auto &item : items) {
            for (auto &product : products) {
                if (product.name == item.first.name) {
                    product.quantity -= item.second;
                    break;
                }
            }
        }

        money += totalPrice;

        /*std::cout << "Inventory after sale: " << std::endl;
        for (const auto &product : products) {
            std::cout << "Product: " << product.name << ", Quantity: " << product.quantity << std::endl;
        }
        std::cout << "Total money: " << money << std::endl;
        std::cout << std::endl;*/

        bills.push_back({std::move(items), totalPrice});
    }

    void inventoryCheck() {

        std::lock_guard<std::mutex> lock(productsMutex);
        std::lock_guard<std::mutex> moneyLock(moneyMutex);
        std::lock_guard<std::mutex> billsLock(billsMutex);

        double totalInventoryValue = 0.0;
        for (const auto &product : products) {
            totalInventoryValue += product.price * product.quantity;
        }

        double totalBillsValue = 0.0;
        for (const auto &bill : bills) {
            totalBillsValue += bill.totalPrice;
        }

        std::cout << "Inventory checked. Total money: " << money << ", Total inventory value: " << totalInventoryValue
                  << ", Total bills value: " << totalBillsValue << std::endl;
    }
};


void performSale(Inventory &inventory) {
    std::vector<std::pair<Product, int>> items;
    double totalPrice = 0.0;
    for (auto &product : inventory.products) {
        int quantitySold = (rand() % (product.quantity + 1)) / 2;
        if (quantitySold > 0) {
            items.emplace_back(product, quantitySold);
            totalPrice += product.price * quantitySold;
        }
    }

    inventory.sell(items, totalPrice);
    //inventory.inventoryCheck();
}

int main() {
    Inventory inventory;

    inventory.products.emplace_back("Bukayo Saka", 1.0, 5000000);
    inventory.products.emplace_back("Nikola Jokic", 2.0, 3000000);
    inventory.products.emplace_back("Lewis Hamilton", 1.5, 400000);
    inventory.products.emplace_back("Novak Djokovic", 5.0, 1500000);

    auto start = std::chrono::steady_clock::now();

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(performSale, std::ref(inventory));
    }

    for (auto &thread : threads) {
        thread.join();
    }

    inventory.inventoryCheck();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken: " << elapsed_seconds.count() << " seconds." << std::endl;

    return 0;
}
