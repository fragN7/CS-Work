#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::vector<int> vector1 = {1, 2, 3, 4, 5};
std::vector<int> vector2 = {6, 7, 8, 9, 10};
std::vector<int> products;
int idx = 0;
int result = 0;

void producer() {
    for (size_t i = 0; i < vector1.size(); ++i) {
        std::unique_lock<std::mutex> lck(mtx);
        int product = vector1[i] * vector2[i];
        std::cout << "Producer calculated product: " << product << std::endl;
        products.push_back(product);
        idx++;
        cv.notify_one();
        if (i < vector1.size() - 1) {
            cv.wait(lck);
        }
    }
}

void consumer() {
    for (size_t i = 0; i < vector1.size(); ++i) {
        std::unique_lock<std::mutex> lck(mtx);
        while (idx <= i) {
            cv.wait(lck);
        }
        result += products[i];
        std::cout << "Consumer processed product: " << result << std::endl;
        cv.notify_one();
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);
    prod.join();
    cons.join();

    return 0;
}
