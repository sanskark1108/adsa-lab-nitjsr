#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 20
#define INF INT_MAX

int n;
int dist[MAX][MAX];
int dp[1<<MAX][MAX];

int tsp(int mask, int pos) {
    if (mask == (1<<n) - 1) return dist[pos][0]; // back to start

    if (dp[mask][pos] != -1) return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city)) && dist[pos][city] != INF) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            if (newAns < ans) ans = newAns;
        }
    }
    return dp[mask][pos] = ans;
}

int main() {
    // Example: initialize distances (here random or predefined)
    n = 10;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            dist[i][j] = (i == j) ? INF : rand()%100 + 1;

    // Initialize dp with -1
    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;

    clock_t start = clock();
    int answer = tsp(1, 0);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Minimum TSP cost: %d\n", answer);
    printf("Time taken: %.4f seconds\n", time_taken);

    return 0;
}
