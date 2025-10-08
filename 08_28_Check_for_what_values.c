#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 20 // limit due to combinatorial explosion

int adj[MAX][MAX], n, e, m;

// Check if all vertices in subset form a clique
int isClique(int subset[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (!adj[subset[i]][subset[j]])
                return 0;
    return 1;
}

int hasClique() {
    int subset[MAX];
    int total = 1 << n; // 2^n subsets
    for (int mask = 0; mask < total; mask++) {
        int count = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i))
                subset[count++] = i;
        if (count == m && isClique(subset, m))
            return 1;
    }
    return 0;
}

int main() {
    printf("Enter number of vertices (n <= %d): ", MAX);
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);
    printf("Enter clique size to check (m <= n): ");
    scanf("%d", &m);

    if (m > n || n > MAX) {
        printf("Invalid input. Max supported n is %d\n", MAX);
        return 1;
    }

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter %d edges (u v) 0-based:\n", e);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    if (hasClique())
        printf("Graph contains a clique of size %d.\n", m);
    else
        printf("Graph does NOT contain a clique of size %d.\n", m);

    return 0;
}
