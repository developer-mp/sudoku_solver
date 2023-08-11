#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <chrono>
#include <vector>

const int N = 9;
const int K = 3;
const int T = 2000;

class SudokuSolver {
public:
    SudokuSolver();
    void setCell(int row, int col, int value, bool userInput);
    int getCell(int row, int col) const;
    bool solveSudoku(int timeoutMillis);
    bool isUserInput(int row, int col) const;

private:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> userInputGrid;

    bool isValid(int row, int col, int num);
    bool solveRecursive(int timeoutMillis, std::chrono::time_point<std::chrono::high_resolution_clock> startTime);
    bool findEmptyCell(int &row, int &col);
};

#endif

