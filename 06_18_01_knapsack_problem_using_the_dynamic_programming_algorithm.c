#include <stdio.h>

// A utility function that returns the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve 0/1 Knapsack problem using dynamic programming
int knapsack(int W, int wt[], int val[], int n) {
    int i, w;
    int K[n + 1][W + 1];

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    // Uncomment below code to print the table (optional debug)
    /*
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            printf("%d\t", K[i][w]);
        }
        printf("\n");
    }
    */

    return K[n][W]; // Maximum value that can be put in a knapsack of capacity W
}

// Example usage
int main() {
    int val[] = {60, 100, 120};   // values of items
    int wt[] = {10, 20, 30};      // weights of items
    int W = 50;                   // capacity of knapsack
    int n = sizeof(val) / sizeof(val[0]);  // number of items

    int maxValue = knapsack(W, wt, val, n);
    printf("Maximum value in Knapsack = %d\n", maxValue);

    return 0;
}
