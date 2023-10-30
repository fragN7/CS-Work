#include <iostream>
#include <utility>
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

    Bill(std::vector<std::pair<Product, int>> items, double totalPrice) : items(std::move(items)), totalPrice(totalPrice) {}
};

struct Inventory {

    std::vector<Product> products;
    double money{};
    std::vector<Bill> bills;

    std::mutex productsMutex;
    std::mutex moneyMutex;
    std::mutex billsMutex;

    void sell() {
        std::lock_guard<std::mutex> lock(productsMutex);
        std::lock_guard<std::mutex> moneyLock(moneyMutex);
        std::lock_guard<std::mutex> billsLock(billsMutex);

        int iterationCount = 0;

        for (auto it = bills.begin(); it != bills.end(); ) {
            for (const auto &productItems : it->items) {
                for (auto &prod : products) {
                    if (productItems.first.name == prod.name) {
                        prod.quantity -= productItems.second;
                    }
                }
            }
            money += it->totalPrice;
            it = bills.erase(it);

            if (++iterationCount % 49 == 0) {
                inventoryCheck();
            }
        }
    }

    void inventoryCheck() {

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

    while (true) {
        inventory.sell();
        std::lock_guard<std::mutex> billsLock(inventory.billsMutex);
        if (inventory.bills.empty()) {
            break;
        }
    }
}

std::vector<std::pair<Product, int>> generateRandomBills(const std::vector<Product> &products) {
    std::vector<std::pair<Product, int>> billItems;

    for(int i = 0; i <= 5; i++){
        int index = rand() % 4;
        int quantitySold = (rand() % (50));
        if (quantitySold > 0) {
            billItems.emplace_back(products[index], quantitySold);
        }
    }

    return billItems;
}

int main() {
    Inventory inventory;

    std::vector<Product> products;
    products.emplace_back("Bukayo Saka", 1.0, 500000);
    products.emplace_back("Nikola Jokic", 2.0, 30000);
    products.emplace_back("Lewis Hamilton", 1.5, 40000);
    products.emplace_back("Novak Djokovic", 5.0, 15000);

    inventory.products.emplace_back("Bukayo Saka", 1.0, 50000);
    inventory.products.emplace_back("Nikola Jokic", 2.0, 30000);
    inventory.products.emplace_back("Lewis Hamilton", 1.5, 40000);
    inventory.products.emplace_back("Novak Djokovic", 5.0, 15000);

    std::vector<Bill> bills;

    for(int i = 0; i < 500; i++){
        auto productsBill = generateRandomBills(products);
        double money = 0;

        for(const auto& bill: productsBill){
            money += bill.first.price * bill.second;
        }
        inventory.bills.emplace_back(productsBill, money);
    }

    inventory.inventoryCheck();

    auto start = std::chrono::steady_clock::now();

    std::vector<std::thread> threads;
    for (int i = 0; i < 16; ++i) {
        threads.emplace_back(performSale, std::ref(inventory));
    }

    for (auto &thread : threads) {
        thread.join();
    }

    auto end = std::chrono::steady_clock::now();

    inventory.inventoryCheck();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken: " << elapsed_seconds.count() << " seconds." << std::endl;

    return 0;
}
