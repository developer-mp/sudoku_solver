#include "sudokusolver.h"

SudokuSolver::SudokuSolver() {
    grid.resize(N, std::vector<int>(N, 0));
    userInputGrid.resize(N, std::vector<bool>(N, false));
}

void SudokuSolver::setCell(int row, int col, int value, bool userInput) {
    grid[row][col] = value;
    userInputGrid[row][col] = userInput;
}

bool SudokuSolver::isUserInput(int row, int col) const {
    return userInputGrid[row][col];
}

int SudokuSolver::getCell(int row, int col) const {
    return grid[row][col];
}

bool SudokuSolver::isValid(int row, int col, int num) {
    for (int i = 0; i < N; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    int startRow = row - row % K;
    int startCol = col - col % K;
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool SudokuSolver::solveRecursive(int timeoutMillis, std::chrono::time_point<std::chrono::high_resolution_clock> startTime) {
    int row, col;
    if (!findEmptyCell(row, col)) {
        return true;
    }

    for (int num = 1; num <= N; ++num) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;

            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
            if (elapsedTime >= timeoutMillis) {
                return false;
            }
            if (solveRecursive(timeoutMillis, startTime)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }

    return false;
}

bool SudokuSolver::solveSudoku(int timeoutMillis) {
    auto startTime = std::chrono::high_resolution_clock::now();
    return solveRecursive(timeoutMillis, startTime);
}

bool SudokuSolver::findEmptyCell(int &row, int &col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}
