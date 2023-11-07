#include <iostream>
#include <vector>
#include <thread>

int computeElement(const std::vector<std::vector<int>>& matrixA, const std::vector<std::vector<int>>& matrixB, int row, int col, int matrixSize) {
    int result = 0;
    for (int i = 0; i < matrixSize; ++i) {
        result += matrixA[row][i] * matrixB[i][col];
    }
    return result;
}

void consecutiveElementsRowByRow(std::vector<std::vector<int>>& matrixA, std::vector<std::vector<int>>& matrixB, std::vector<std::vector<int>>& resultMatrix, int startRow, int endRow, int matrixSize) {
    for (int i = startRow; i <= endRow; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            resultMatrix[i][j] = computeElement(matrixA, matrixB, i, j, matrixSize);
        }
    }
}

int main() {
    int matrixSize;
    std::cout << "Enter the size of the matrix:";
    std::cin >> matrixSize;

    std::vector<std::vector<int>> matrixA(matrixSize, std::vector<int>(matrixSize, 1));
    std::vector<std::vector<int>> matrixB(matrixSize, std::vector<int>(matrixSize, 2));
    std::vector<std::vector<int>> resultMatrix(matrixSize, std::vector<int>(matrixSize, 0));

    std::vector<std::thread> threads;
    int tasks = 4;
    int elementsPerTask = matrixSize / tasks;
    for (int i = 0; i < tasks; ++i) {
        int startRow = i * elementsPerTask;
        int endRow = (i + 1) * elementsPerTask - 1;
        if (i == tasks - 1) {
            endRow = matrixSize - 1;
        }
        threads.emplace_back(consecutiveElementsRowByRow, std::ref(matrixA), std::ref(matrixB), std::ref(resultMatrix), startRow, endRow, matrixSize);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    for (const auto &row : resultMatrix) {
        for (const auto &element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
