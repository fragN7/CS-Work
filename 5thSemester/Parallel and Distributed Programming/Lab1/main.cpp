#include <iostream>
#include <mutex>

struct Account {
    unsigned balance{};
    std::mutex mtx;
};

bool transfer(Account* a, Account* b, unsigned amount) {
    a->mtx.lock();
    if(a->balance < amount) {
        a->mtx.unlock();
        return false;
    }
    a->balance -= amount;
    a->mtx.unlock();
    b->mtx.lock();
    b->balance += amount;
    b->mtx.unlock();
    return true;
}

int main() {

    Account acc1;
    acc1.balance = 100;

    Account acc2;
    acc2.balance = 50;

    // Example 1: Successful transfer
    if (transfer(&acc1, &acc2, 30)) {
        std::cout << "Transfer successful." << std::endl;
    } else {
        std::cout << "Insufficient funds for transfer." << std::endl;
    }

    // Example 2: Insufficient funds
    if (transfer(&acc1, &acc2, 1000)) {
        std::cout << "Transfer successful." << std::endl;
    } else {
        std::cout << "Insufficient funds for transfer." << std::endl;
    }

    return 0;
}
