#include <stdio.h>

int n; // Number of items
int maxWeight; // Capacity of the knapsack

int weights[100]; // Weights of the items
int profits[100]; // Profits of the items

int maxProfit = 0; // Stores the maximum profit found so far

// Function to check if including item i is promising
int isPromising(int i, int weight, int profit) {
    int j = i + 1;
    int totalWeight = weight;
    float bound = profit;

    // Use fractional knapsack approach to calculate upper bound
    while (j < n && totalWeight + weights[j] <= maxWeight) {
        totalWeight += weights[j];
        bound += profits[j];
        j++;
    }

    if (j < n)
        bound += (maxWeight - totalWeight) * (float)profits[j] / weights[j];

    return bound > maxProfit;
}

// Backtracking function
void knapsack(int i, int profit, int weight) {
    if (weight <= maxWeight && profit > maxProfit) {
        maxProfit = profit;
    }

    if (i == n - 1) return;

    if (isPromising(i, weight, profit)) {
        // Include item i+1
        knapsack(i + 1, profit + profits[i + 1], weight + weights[i + 1]);

        // Exclude item i+1
        knapsack(i + 1, profit, weight);
    }
}

int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter the capacity of knapsack: ");
    scanf("%d", &maxWeight);

    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &weights[i]);

    printf("Enter profits of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &profits[i]);

    // Sort items by profit/weight ratio (greedy criteria for bounding)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            float r1 = (float)profits[i] / weights[i];
            float r2 = (float)profits[j] / weights[j];
            if (r1 < r2) {
                // Swap profits
                int temp = profits[i];
                profits[i] = profits[j];
                profits[j] = temp;
                // Swap weights
                temp = weights[i];
                weights[i] = weights[j];
                weights[j] = temp;
            }
        }
    }

    knapsack(-1, 0, 0);

    printf("Maximum profit: %d\n", maxProfit);
    return 0;
}

