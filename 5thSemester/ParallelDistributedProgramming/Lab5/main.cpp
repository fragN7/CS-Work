#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>

struct Polynomial {
    std::vector<int> coefficients;

    Polynomial(std::vector<int> coeffs) : coefficients(coeffs) {}

    Polynomial operator-(const Polynomial& other) const {
        size_t size = std::max(coefficients.size(), other.coefficients.size());
        std::vector<int> result(size, 0);

        for (size_t i = 0; i < size; ++i) {
            int coef1 = (i < coefficients.size()) ? coefficients[i] : 0;
            int coef2 = (i < other.coefficients.size()) ? other.coefficients[i] : 0;
            result[i] = coef1 - coef2;
        }

        // Remove leading zeros
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }

        return Polynomial(result);
    }
};

// Regular O(n^2) polynomial multiplication (Sequential)
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

// Function to perform polynomial multiplication in a thread
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

// Regular O(n^2) polynomial multiplication (Parallelized)
Polynomial multiplyPolynomialsRegularParallel(const Polynomial& poly1, const Polynomial& poly2) {
    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();
    std::vector<int> result(m + n - 1, 0);
    std::mutex mtx;

    int num_threads = std::thread::hardware_concurrency(); // Number of available threads

    std::vector<std::thread> threads;
    int chunk_size = m / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? m : (i + 1) * chunk_size;
        threads.emplace_back(multiplyPartialPolynomials, std::ref(poly1), std::ref(poly2),
                             std::ref(result), start, end, std::ref(mtx));
    }

    for (auto& t : threads) {
        t.join();
    }

    return Polynomial(result);
}

// Karatsuba polynomial multiplication (Sequential)
Polynomial multiplyPolynomialsKaratsubaSequential(const Polynomial& poly1, const Polynomial& poly2) {
    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();

    if (m == 0 || n == 0) {
        return Polynomial(std::vector<int>());
    }

    if (m == 1 || n == 1) {
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

    Polynomial a_sum = a0;
    for (int i = 0; i < a1.coefficients.size(); ++i) {
        if (i < a_sum.coefficients.size()) {
            a_sum.coefficients[i] += a1.coefficients[i];
        } else {
            a_sum.coefficients.push_back(a1.coefficients[i]);
        }
    }

    Polynomial b_sum = b0;
    for (int i = 0; i < b1.coefficients.size(); ++i) {
        if (i < b_sum.coefficients.size()) {
            b_sum.coefficients[i] += b1.coefficients[i];
        } else {
            b_sum.coefficients.push_back(b1.coefficients[i]);
        }
    }

    Polynomial z1 = multiplyPolynomialsKaratsubaSequential(a_sum, b_sum) - z0 - z2;

    std::vector<int> result(2 * half + std::max(a1.coefficients.size(), b1.coefficients.size()) - 1, 0);
    for (int i = 0; i < z0.coefficients.size(); ++i) {
        result[i] += z0.coefficients[i];
    }
    for (int i = 0; i < z1.coefficients.size(); ++i) {
        result[i + half] += z1.coefficients[i];
    }
    for (int i = 0; i < z2.coefficients.size(); ++i) {
        result[i + 2 * half] += z2.coefficients[i];
    }

    return Polynomial(result);
}


// Karatsuba polynomial multiplication (Parallelized)
Polynomial multiplyPolynomialsKaratsubaParallel(const Polynomial& poly1, const Polynomial& poly2) {
    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();

    if (m == 0 || n == 0) {
        return Polynomial(std::vector<int>());
    }

    if (m == 1 || n == 1) {
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

    auto z0_future = std::async(std::launch::async, multiplyPolynomialsKaratsubaParallel, std::ref(a0), std::ref(b0));
    auto z2_future = std::async(std::launch::async, multiplyPolynomialsKaratsubaParallel, std::ref(a1), std::ref(b1));

    Polynomial z0 = z0_future.get();
    Polynomial z2 = z2_future.get();

    Polynomial a_sum = a0;
    for (int i = 0; i < a1.coefficients.size(); ++i) {
        if (i < a_sum.coefficients.size()) {
            a_sum.coefficients[i] += a1.coefficients[i];
        } else {
            a_sum.coefficients.push_back(a1.coefficients[i]);
        }
    }

    Polynomial b_sum = b0;
    for (int i = 0; i < b1.coefficients.size(); ++i) {
        if (i < b_sum.coefficients.size()) {
            b_sum.coefficients[i] += b1.coefficients[i];
        } else {
            b_sum.coefficients.push_back(b1.coefficients[i]);
        }
    }

    auto z1_future = std::async(std::launch::async, multiplyPolynomialsKaratsubaParallel, std::ref(a_sum), std::ref(b_sum));
    Polynomial z1 = z1_future.get() - z0 - z2;

    std::vector<int> result(2 * half + std::max(a1.coefficients.size(), b1.coefficients.size()) - 1, 0);
    for (int i = 0; i < z0.coefficients.size(); ++i) {
        result[i] += z0.coefficients[i];
    }
    for (int i = 0; i < z1.coefficients.size(); ++i) {
        result[i + half] += z1.coefficients[i];
    }
    for (int i = 0; i < z2.coefficients.size(); ++i) {
        result[i + 2 * half] += z2.coefficients[i];
    }

    return Polynomial(result);
}


int main() {
    // Test polynomials
    Polynomial poly1({1, 2, 3}); // 1 + 2x + 3x^2
    Polynomial poly2({2, 1});    // 2 + x

    // Regular Multiplication (Sequential)
    auto startRegularSequential = std::chrono::steady_clock::now();
    Polynomial resultRegularSequential = multiplyPolynomialsRegularSequential(poly1, poly2);
    auto endRegularSequential = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedRegularSequential = endRegularSequential - startRegularSequential;
    std::cout << "Regular Multiplication (Sequential) Time: " << elapsedRegularSequential.count() << " seconds\n";
    std::cout << "Regular Multiplication (Sequential) Result: ";
    std::cout << std::endl;

    // Regular Multiplication (Parallel)
    auto startRegularParallel = std::chrono::steady_clock::now();
    Polynomial resultRegularParallel = multiplyPolynomialsRegularParallel(poly1, poly2);
    auto endRegularParallel = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedRegularParallel = endRegularParallel - startRegularParallel;
    std::cout << "Regular Multiplication (Parallel) Time: " << elapsedRegularParallel.count() << " seconds\n";
    std::cout << "Regular Multiplication (Parallel) Result: ";
    std::cout << std::endl;

    // Karatsuba Multiplication (Sequential)
    auto startKaratsubaSequential = std::chrono::steady_clock::now();
    Polynomial resultKaratsubaSequential = multiplyPolynomialsKaratsubaSequential(poly1, poly2);
    auto endKaratsubaSequential = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedKaratsubaSequential = endKaratsubaSequential - startKaratsubaSequential;
    std::cout << "Karatsuba Multiplication (Sequential) Time: " << elapsedKaratsubaSequential.count() << " seconds\n";
    std::cout << "Karatsuba Multiplication (Sequential) Result: ";
    std::cout << std::endl;

    // Karatsuba Multiplication (Parallel) - Currently implemented as Sequential
    auto startKaratsubaParallel = std::chrono::steady_clock::now();
    Polynomial resultKaratsubaParallel = multiplyPolynomialsKaratsubaParallel(poly1, poly2);
    auto endKaratsubaParallel = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedKaratsubaParallel = endKaratsubaParallel - startKaratsubaParallel;
    std::cout << "Karatsuba Multiplication (Parallel) Time: " << elapsedKaratsubaParallel.count() << " seconds\n";
    std::cout << "Karatsuba Multiplication (Parallel) Result: ";
    std::cout << std::endl;

    return 0;
}


