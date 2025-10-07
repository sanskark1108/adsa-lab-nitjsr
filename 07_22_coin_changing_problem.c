#include <stdio.h>

/**
 * @brief Finds the minimum coins for a given amount using a greedy approach.
 * @param coins An array of coin denominations, sorted in descending order.
 * @param n The number of coin denominations.
 * @param amount The total amount to make change for.
 */
void findMinCoins(int coins[], int n, int amount) {
    printf("Coins used: ");
    // Iterate through all coins from largest to smallest
    for (int i = 0; i < n; i++) {
        // While the current coin can be used
        while (amount >= coins[i]) {
            // Subtract the coin's value and print it
            amount -= coins[i];
            printf("%d ", coins[i]);
        }
    }
    printf("\n");
}

int main() {
    // Note: The coin denominations must be sorted in descending order.
    int coins[] = {100, 50, 20, 10, 5, 2, 1};
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount = 93;

    printf("Finding minimum coins for amount: %d\n", amount);
    findMinCoins(coins, n, amount);

    return 0;
}