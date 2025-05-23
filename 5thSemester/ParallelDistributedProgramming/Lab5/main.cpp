#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
#include <algorithm>

struct Polynomial {
    std::vector<int> coefficients;

    Polynomial(std::vector<int> coeffs) : coefficients(coeffs) {}

    Polynomial() = default;

    void padZeros(int n) {
        coefficients.insert(coefficients.begin(), n, 0);
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        result.coefficients.resize(std::max(coefficients.size(), other.coefficients.size()), 0);

        for (size_t i = 0; i < coefficients.size(); ++i) {
            result.coefficients[i] += coefficients[i];
        }

        for (size_t i = 0; i < other.coefficients.size(); ++i) {
            result.coefficients[i] += other.coefficients[i];
        }

        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;
        result.coefficients.resize(std::max(coefficients.size(), other.coefficients.size()), 0);

        for (size_t i = 0; i < coefficients.size(); ++i) {
            result.coefficients[i] += coefficients[i];
        }

        for (size_t i = 0; i < other.coefficients.size(); ++i) {
            result.coefficients[i] -= other.coefficients[i];
        }

        return result;
    }
};

Polynomial multiplyPolynomialsRegularSequential(const Polynomial& poly1, const Polynomial& poly2) {
    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();
    std::vector<int> result(m + n - 1, 0);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i + j] += poly1.coefficients[i] * poly2.coefficients[j];
        }
    }

    return Polynomial(result);
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    int degree = static_cast<int>(poly.coefficients.size()) - 1;

    for (int i = degree; i >= 0; --i) {
        if (poly.coefficients[i] != 0) {
            if (i != degree) {
                os << ((poly.coefficients[i] > 0) ? " + " : " - ");
            }

            if (std::abs(poly.coefficients[i]) != 0 || i == 0) {
                os << std::abs(poly.coefficients[i]);
                if (i != 0) {
                    os << "x";
                    if (i != 1) {
                        os << "^" << i;
                    }
                }
            } else {
                if (i == 1) {
                    os << "x";
                }
            }
        }
    }

    return os;
}

void multiplyPartialPolynomials(const Polynomial& poly1, const Polynomial& poly2,
                                std::vector<int>& result, int start, int end, std::mutex& mtx) {
    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < n; ++j) {
            mtx.lock();
            result[i + j] += poly1.coefficients[i] * poly2.coefficients[j];
            mtx.unlock();
        }
    }
}

Polynomial multiplyPolynomialsRegularParallel(const Polynomial& poly1, const Polynomial& poly2) {
    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();
    std::vector<int> result(m + n - 1, 0);
    std::mutex mtx;

    int num_threads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;
    int chunk_size = std::min(m / num_threads + 1, m); // Calculate chunk size

    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = std::min((i + 1) * chunk_size, m); // Cap the end at m
        threads.emplace_back(multiplyPartialPolynomials, std::ref(poly1), std::ref(poly2),
                             std::ref(result), start, end, std::ref(mtx));
    }

    for (auto& t : threads) {
        t.join();
    }

    return Polynomial(result);
}

Polynomial multiplyPolynomialsKaratsubaSequential(const Polynomial& poly1, const Polynomial& poly2) {
    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();

    if (m == 0 || n == 0) {
        return Polynomial(std::vector<int>());
    }

    if (m < 16 || n < 16) {
        std::vector<int> result(m + n - 1, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i + j] += poly1.coefficients[i] * poly2.coefficients[j];
            }
        }
        return Polynomial(result);
    }

    int half = std::max(m, n) / 2;

    Polynomial a0(std::vector<int>(poly1.coefficients.begin(), poly1.coefficients.begin() + std::min(half, m)));
    Polynomial a1(std::vector<int>(poly1.coefficients.begin() + std::min(half, m), poly1.coefficients.end()));
    Polynomial b0(std::vector<int>(poly2.coefficients.begin(), poly2.coefficients.begin() + std::min(half, n)));
    Polynomial b1(std::vector<int>(poly2.coefficients.begin() + std::min(half, n), poly2.coefficients.end()));

    Polynomial z0 = multiplyPolynomialsKaratsubaSequential(a0, b0);
    Polynomial z2 = multiplyPolynomialsKaratsubaSequential(a1, b1);

    a0.coefficients.resize(std::max(a0.coefficients.size(), b1.coefficients.size()), 0);
    b1.coefficients.resize(std::max(a0.coefficients.size(), b1.coefficients.size()), 0);

    Polynomial a_sum = a0 + a1;
    Polynomial b_sum = b0 + b1;

    Polynomial z1 = multiplyPolynomialsKaratsubaSequential(a_sum, b_sum) - z0 - z2;

    z0.padZeros(2 * half);
    z1.padZeros(half);

    return z0 + z1 + z2;
}

Polynomial multiplyPolynomialsKaratsubaParallel(const Polynomial& poly1, const Polynomial& poly2) {
    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();

    if (m == 0 || n == 0) {
        return Polynomial(std::vector<int>());
    }

    if (m > 16 || n > 16) {
        std::vector<int> result(m + n - 1, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i + j] += poly1.coefficients[i] * poly2.coefficients[j];
            }
        }
        return Polynomial(result);
    }

    int half = std::max(m, n) / 2;

    Polynomial a0(std::vector<int>(poly1.coefficients.begin(), poly1.coefficients.begin() + std::min(half, m)));
    Polynomial a1(std::vector<int>(poly1.coefficients.begin() + std::min(half, m), poly1.coefficients.end()));
    Polynomial b0(std::vector<int>(poly2.coefficients.begin(), poly2.coefficients.begin() + std::min(half, n)));
    Polynomial b1(std::vector<int>(poly2.coefficients.begin() + std::min(half, n), poly2.coefficients.end()));

    auto z0_async = std::async(std::launch::async, multiplyPolynomialsKaratsubaParallel, std::ref(a0), std::ref(b0));
    auto z2_async  = std::async(std::launch::async, multiplyPolynomialsKaratsubaParallel, std::ref(a1), std::ref(b1));

    Polynomial z0 = z0_async.get();
    Polynomial z2 = z2_async.get();

    a0.coefficients.resize(std::max(a0.coefficients.size(), b1.coefficients.size()), 0);
    b1.coefficients.resize(std::max(a0.coefficients.size(), b1.coefficients.size()), 0);

    Polynomial a_sum = a0 + a1;
    Polynomial b_sum = b0 + b1;

    auto z1_async = std::async(std::launch::async, multiplyPolynomialsKaratsubaParallel, std::ref(a_sum), std::ref(b_sum));
    Polynomial z1 = z1_async.get() - z0 - z2;

    z0.padZeros(2 * half);
    z1.padZeros(half);

    return z0 + z1 + z2;
}


int main() {
   /* Polynomial poly1({-1, 1});
    Polynomial poly2({1, 1});*/

    srand(static_cast<unsigned int>(time(nullptr)));

    int vectorSize = 10000;// Change this to the size you want
    std::vector<int> randVector1(vectorSize);
    std::vector<int> randVector2(vectorSize);

    // Fill the vector with random numbers between 1 and 10
    for (int i = 0; i < vectorSize; ++i) {
        randVector1[i] = rand() % 10 + 1; // Generates a random number between 1 and 10
        randVector2[i] = rand() % 10 + 1; // Generates a random number between 1 and 10
    }

    Polynomial poly1(randVector1);
    Polynomial poly2(randVector2);

    auto startRegularSequential = std::chrono::steady_clock::now();
    Polynomial resultRegularSequential = multiplyPolynomialsRegularSequential(poly1, poly2);
    auto endRegularSequential = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedRegularSequential = endRegularSequential - startRegularSequential;
    std::cout << "Regular Multiplication (Parallel) Time: " << elapsedRegularSequential.count() << " seconds\n";
    //std::cout << "Regular Multiplication (Sequential) Result: " << resultRegularSequential << std::endl;
    std::cout << std::endl;

    auto startRegularParallel = std::chrono::steady_clock::now();
    Polynomial resultRegularParallel = multiplyPolynomialsRegularParallel(poly1, poly2);
    auto endRegularParallel = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedRegularParallel = endRegularParallel - startRegularParallel;
    std::cout << "Regular Multiplication (Sequential) Time: " << elapsedRegularParallel.count() << " seconds\n";
    //std::cout << "Regular Multiplication (Parallel) Result: " << resultRegularParallel << std::endl;
    std::cout << std::endl;

    auto startKaratsubaSequential = std::chrono::steady_clock::now();
    Polynomial resultKaratsubaSequential = multiplyPolynomialsKaratsubaSequential(poly1, poly2);
    auto endKaratsubaSequential = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedKaratsubaSequential = endKaratsubaSequential - startKaratsubaSequential;
    std::cout << "Karatsuba Multiplication (Parallel) Time: " << elapsedKaratsubaSequential.count() << " seconds\n";
    //std::cout << "Karatsuba Multiplication (Sequential) Result: " << resultRegularParallel << std::endl;
    std::cout << std::endl;

    auto startKaratsubaParallel = std::chrono::steady_clock::now();
    Polynomial resultKaratsubaParallel = multiplyPolynomialsKaratsubaParallel(poly1, poly2);
    auto endKaratsubaParallel = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedKaratsubaParallel = endKaratsubaParallel - startKaratsubaParallel;
    std::cout << "Karatsuba Multiplication (Sequential) Time: " << elapsedKaratsubaParallel.count() << " seconds\n";
    //std::cout << "Karatsuba Multiplication (Parallel) Result: " << resultRegularParallel << std::endl;
    std::cout << std::endl;

    return 0;
}


