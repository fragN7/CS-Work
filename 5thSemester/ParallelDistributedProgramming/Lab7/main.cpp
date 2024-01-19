#include <iostream>
#include <mpi.h>
#include <utility>
#include <vector>
#include <chrono>

struct Polynomial {
    std::vector<int> coefficients;

    explicit Polynomial(std::vector<int> coeffs) : coefficients(std::move(coeffs)) {}

    Polynomial() = default;

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

    Polynomial addPadding(int n) const {
        std::vector<int> paddedCoeffs(coefficients);
        paddedCoeffs.insert(paddedCoeffs.begin(), n, 0);
        return Polynomial(paddedCoeffs);
    }

    Polynomial slice(int start, int end) const {
        std::vector<int> slicedCoeffs(coefficients.begin() + start, coefficients.begin() + end);
        return Polynomial(slicedCoeffs);
    }
};

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

Polynomial multiplyPolynomialsRegularMPI(const Polynomial& poly1, const Polynomial& poly2) {
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();
    int result_size = m + n - 1;

    std::vector<int> local_result(result_size, 0);

    std::vector<int> coeffs2 = poly2.coefficients;

    MPI_Bcast(coeffs2.data(), n, MPI_INT, 0, MPI_COMM_WORLD);

    int local_start = world_rank * (m / world_size);
    int local_end = (world_rank == world_size - 1) ? m : (world_rank + 1) * (m / world_size);

    for (int i = local_start; i < local_end; ++i) {
        for (int j = 0; j < n; ++j) {
            local_result[i + j] += poly1.coefficients[i] * poly2.coefficients[j];
        }
    }

    // Gather all partial results
    std::vector<int> global_result(result_size, 0);
    MPI_Reduce(local_result.data(), global_result.data(), result_size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        return Polynomial(global_result);
    } else {
        return {};
    }
}

Polynomial multiplyPolynomialsKaratsubaMPI(const Polynomial& poly1, const Polynomial& poly2) {
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int m = poly1.coefficients.size();
    int n = poly2.coefficients.size();
    int resultSize = m + n - 1;

    if (world_size > resultSize) {
        if (world_rank == 0) {
            std::cout << "Error: Too many processes for this multiplication." << std::endl;
        }
        MPI_Finalize();
        exit(1);
    }

    std::vector<int> localResult(resultSize, 0);
    std::vector<int> globalResult(resultSize, 0);

    int localStart = world_rank * (resultSize / world_size);
    int localEnd = (world_rank == world_size - 1) ? resultSize : (world_rank + 1) * (resultSize / world_size);

    if (m <= 16 || n <= 16) {
        for (int i = localStart; i < localEnd; ++i) {
            for (int j = std::max(0, i - n + 1); j < std::min(m, i + 1); ++j) {
                localResult[i] += poly1.coefficients[j] * poly2.coefficients[i - j];
            }
        }
    } else {
        int halfSize = std::max(m, n) / 2;

        Polynomial a0({poly1.coefficients.begin(), poly1.coefficients.begin() + halfSize});
        Polynomial a1({poly1.coefficients.begin() + halfSize, poly1.coefficients.end()});
        Polynomial b0({poly2.coefficients.begin(), poly2.coefficients.begin() + halfSize});
        Polynomial b1({poly2.coefficients.begin() + halfSize, poly2.coefficients.end()});

        Polynomial z0 = multiplyPolynomialsKaratsubaMPI(a0, b0);
        Polynomial z2 = multiplyPolynomialsKaratsubaMPI(a1, b1);
        Polynomial z1 = multiplyPolynomialsKaratsubaMPI(a0 + a1, b0 + b1);

        Polynomial temp = z1 - (z0 + z2);

        for (int i = 0; i < temp.coefficients.size(); ++i) {
            if (i + halfSize < localResult.size()) {
                localResult[i + halfSize] += temp.coefficients[i];
            }
        }

        for (int i = 0; i < z2.coefficients.size(); ++i) {
            if (i + 2 * halfSize < localResult.size()) {
                localResult[i + 2 * halfSize] += z2.coefficients[i];
            }
        }
    }

    MPI_Allreduce(localResult.data(), globalResult.data(), resultSize, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    return Polynomial(globalResult);
}

int main(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    //srand(static_cast<unsigned int>(time(nullptr)));

    int vectorSize = 5;
    std::vector<int> randVector1(vectorSize);
    std::vector<int> randVector2(vectorSize);

    for (int i = 0; i < vectorSize; ++i) {
        randVector1[i] = rand() % 10 + 1; // Generates a random number between 1 and 10
        randVector2[i] = rand() % 10 + 1; // Generates a random number between 1 and 10
    }



    Polynomial poly1(randVector1);



    Polynomial poly2(randVector2);

    std::cout << poly1 << "\n";
    std::cout << poly2 << "\n";

    // Multiply the polynomials using MPI
    auto startRegular = std::chrono::steady_clock::now();
    Polynomial result = multiplyPolynomialsRegularMPI(poly1, poly2);
    auto endRegular = std::chrono::steady_clock::now();
    std::chrono::duration<double> timeRegular = endRegular - startRegular;
    std::cout << "Regular Multiplication Time: " << timeRegular.count() << " seconds\n" << result;

    auto startKaratsuba = std::chrono::steady_clock::now();
    Polynomial resultKaratsuba = multiplyPolynomialsKaratsubaMPI(poly1, poly2);
    auto endKaratsuba = std::chrono::steady_clock::now();
    std::chrono::duration<double> timeKaratsuba = endKaratsuba - startKaratsuba;
    std::cout << "Karatsuba Multiplication Time: " << timeKaratsuba.count() << " seconds\n";

    // Finalize MPI
    MPI_Finalize();

    return 0;
}