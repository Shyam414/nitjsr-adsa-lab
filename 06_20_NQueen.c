#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

#define MAX 20

int board[MAX], n;

int place(int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0;
    return 1;
}

void printSolution() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf(board[i] == j ? "Q " : ". ");
        printf("\n");
    }
    printf("\n");
}

void solve(int row) {
    if (row == n) {
        printSolution();
        return;
    }
    for (int col = 0; col < n; col++) {
        if (place(row, col)) {
            board[row] = col;
            solve(row + 1);
        }
    }
}

int main() {
    printf("Enter N: ");
    scanf("%d", &n);
    solve(0);
    return 0;
}
