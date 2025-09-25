#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int board[MAX];  // board[i] stores the column number of queen placed in row i
int n;           // number of queens (also size of the board)

// Function to check if placing a queen at row `row` and column `col` is safe
int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col ||                 // Same column
            abs(board[i] - col) == abs(i - row)) // Same diagonal
            return 0;
    }
    return 1;
}

// Recursive backtracking function to place queens
void solve(int row) {
    if (row == n) {
        // Found a valid solution, print the board
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i] == j)
                    printf("Q ");
                else
                    printf(". ");
            }
            printf("\n");
        }
        printf("\n");
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;   // Place queen
            solve(row + 1);     // Recurse for next row
            // No need to "unmark" because we overwrite board[row] in the next iteration
        }
    }
}

int main() {
    printf("Enter the number of queens: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Please enter N between 1 and %d.\n", MAX);
        return 1;
    }

    printf("Solutions for %d-Queens problem:\n\n", n);
    solve(0);
    return 0;
}
