#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define size 9
#define unassigned 0

bool findNext(int board[size][size], int* row, int* column);
bool isValid(int board[size][size], int row, int column, int number);
bool isUsedColumn(int board[size][size], int column, int number);
bool isUsedRow(int board[size][size], int row, int number);
bool isUsedBox(int board[size][size], int startRow, int startColumn, int number);
bool solveBoard(int board[size][size]);
void printBoard(int board[size][size]);

int board[size][size] = { {3, 0, 6, 5, 0, 8, 4, 0, 0},
                        { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                        { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                        { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                        { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                        { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                        { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

void main() {
    if (solveBoard(board)) {
        printBoard(board);
    }
    else {
        printf("No solution\n");
    }
}

bool findNext(int board[size][size], int* row, int* column) {
    *row = 0;
    *column = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        *row = i;
        for (j = 0; j < size; j++) {
            *column = j;
            if (board[i][j] == unassigned) {
                return true;
            }
        }
    }
    return false;
}

bool isUsedColumn(int board[size][size], int column, int number) {
    int row;
    for (row = 0; row < size; row++) {
        if (board[row][column] == number) {
            return true;
        }
    }
    return false;
}

bool isUsedRow(int board[size][size], int row, int number) {
    int column;
    for (column = 0; column < size; column++) {
        if (board[row][column] == number) {
            return true;
        }
    }
    return false;
}

bool isUsedBox(int board[size][size], int startRow, int startColumn, int number) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[startRow + i][startColumn + j] == number) {
                return true;
            }
        }
    }
    return false;
}

bool isValid(int board[size][size], int row, int column, int number) {
    if (isUsedRow(board, row, number))
        return false;
    if (isUsedColumn(board, column, number))
        return false;
    if (isUsedRow(board, row, number))
        return false;
    if (isUsedRow(board, row, number))
        return false;
    return true;
}

bool solveBoard(int board[size][size]) {
    int* row, * column, num, i;
    row = (int*)malloc(sizeof(int));
    column = (int*)malloc(sizeof(int));
    if (!findNext(board, row, column)) {
        return true;
    }
    for (num = 1; num <= 9; num++) {
        if (isValid(board, *row, *column, num)) {
            board[*row][*column] = num;
            usleep(400 * 1000);
            for (i = 0; i < 9; i++) {
                printf("\n");
            }
            printBoard(board);
            if (solveBoard(board)) {
                free(row);
                free(column);
                return true;
            }
            board[*row][*column] = unassigned;
        }
    }
    free(row);
    free(column);
    return false;
}

void printBoard(int board[size][size]) {
    int row, column;
    for (row = 0; row < 9; row++) {
        for (column = 0; column < 9; column++) {
            printf("%2d", board[row][column]);
        }
        printf("\n");
    }
}