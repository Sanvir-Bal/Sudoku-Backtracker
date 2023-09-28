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
bool solveBoard(int board[size][size], int input);
bool playBoard(int board[size][size]);
void printBox(int board[size][size], int startRow, int startColumn);
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
    int input;
    printBoard(board);
    printf("What would you like to do?\n");
    printf("(1) Solve the board.\n");
    printf("(2) Visual the board being solved.\n");
    printf("(3) Play as normal.\n");
    scanf("%d", &input);
    switch (input) {
    case 1:
        if (solveBoard(board, input)) {
            printBoard(board);
            printf("Solved\n");
        }
        else {
            printf("No solution\n");
        }
        break;
    case 2:
        if (solveBoard(board, input)) {
            printBoard(board);
            printf("Solved\n");
        }
        else {
            printf("No solution\n");
        }
        break;
    case 3:
        if (playBoard(board)) {
            printf("Congratulations!\n");
        }
        else {
            printf("Sorry that is incorrect.\n");
        }
        break;
    default:
        printf("Not a valid input\n.");
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
    if (isUsedBox(board, row - (row % 3), column - (column % 3), number))
        return false;
    if (!board[row][column] == unassigned)
        return false;
    return true;
}

bool solveBoard(int board[size][size], int input) {
    int* row, * column, num, i;
    row = (int*)malloc(sizeof(int));
    column = (int*)malloc(sizeof(int));
    if (!findNext(board, row, column)) {
        free(row);
        free(column);
        return true;
    }
    for (num = 1; num <= 9; num++) {
        if (isValid(board, *row, *column, num)) {
            board[*row][*column] = num;
            if (input == 2) {
                usleep(200 * 1000);
                for (i = 0; i < 9; i++) {
                    printf("\n");
                }
                printBoard(board);
            }
            if (solveBoard(board, input)) {
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

bool playBoard(int board[size][size]) {
    int answerBox, answerSquare, answer, row, column, rowTemp, columnTemp;
    int* rowCheck, * columnCheck;
    rowCheck = (int*)malloc(sizeof(int));
    columnCheck = (int*)malloc(sizeof(int));
    while (findNext(board, rowCheck, columnCheck)) {
        printBoard(board);
        printf("Which box would you like to play on?\n");
        scanf("%d", &answerBox);
        switch (answerBox) {
        case 1:
            row = 0;
            column = 0;
            printBox(board, row, column);
            break;
        case 2:
            row = 0;
            column = 3;
            printBox(board, row, column);
            break;
        case 3:
            row = 0;
            column = 6;
            printBox(board, row, column);
            break;
        case 4:
            row = 3;
            column = 0;
            printBox(board, row, column);
            break;
        case 5:
            row = 3;
            column = 3;
            printBox(board, row, column);
            break;
        case 6:
            row = 3;
            column = 6;
            printBox(board, row, column);
            break;
        case 7:
            row = 6;
            column = 0;
            printBox(board, row, column);
            break;
        case 8:
            row = 6;
            column = 3;
            printBox(board, row, column);
            break;
        case 9:
            row = 6;
            column = 6;
            printBox(board, row, column);
            break;
        default: printf("Not a valid option\n");
        }
        int check = 0;
        int value;
        while (check == 0) {
            printf("Which square would you like to place your answer on?\n");
            scanf("%d", &answerSquare);
            switch (answerSquare) {
            case 1:
                rowTemp = row;
                columnTemp = column;
                value = board[row][column];
                break;
            case 2:
                rowTemp = row;
                columnTemp = column + 1;
                value = board[row][column + 1];
                break;
            case 3:
                rowTemp = row;
                columnTemp = column + 2;
                value = board[row][column + 2];
                break;
            case 4:
                rowTemp = row + 1;
                columnTemp = column;
                value = board[row + 1][column];
                break;
            case 5:
                rowTemp = row + 1;
                columnTemp = column + 1;
                value = board[row + 1][column + 1];
                break;
            case 6:
                rowTemp = row + 1;
                columnTemp = column + 2;
                value = board[row + 1][column + 2];
                break;
            case 7:
                rowTemp = row + 2;
                columnTemp = column;
                value = board[row + 2][column];
                break;
            case 8:
                rowTemp = row + 2;
                columnTemp = column + 1;
                value = board[row + 2][column + 1];
                break;
            case 9:
                rowTemp = row + 2;
                columnTemp = column + 2;
                value = board[row + 2][column + 2];
                break;
            default: printf("Not a valid option\n");
            }
            if (value == unassigned)
                check = 1;
        }
        printf("What is your answer?\n");
        scanf("%d", &answer);
        if (!isValid(board, rowTemp, columnTemp, answer)) {
            return false;
        }
        else {
            board[rowTemp][columnTemp] = answer;
        }
    }
    return true;
}

void printBox(int board[size][size], int startRow, int startColumn) {
    int i, j;
    for (i = startRow; i < 3 + startRow; i++) {
        for (j = startColumn; j < 3 + startColumn; j++) {
            printf("%2d", board[i][j]);
        }
        printf("\n");
    }
}

void printBoard(int board[size][size]) {
    int row, column;
    for (row = 0; row < 9; row++) {
        for (column = 0; column < 9; column++) {
            printf("%2d", board[row][column]);
        }
        printf("\n");
    }
    printf("\n");
}
