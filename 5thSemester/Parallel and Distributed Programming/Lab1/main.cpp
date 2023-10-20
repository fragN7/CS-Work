#include <iostream>
#include <mutex>

struct Account {
    unsigned balance;
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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
