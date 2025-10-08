#include <stdio.h>

#define MAX 1000

int adj[MAX][MAX], visited[MAX], stack[MAX];
int top = 0;

void dfsTopo(int u, int n) {
    visited[u] = 1;
    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v])
            dfsTopo(v, n);
    }
    stack[top++] = u;  // Push to stack after visiting neighbors
}

void topologicalSort(int n) {
    for (int i = 0; i < n; i++) visited[i] = 0;
    top = 0;
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfsTopo(i, n);

    printf("Topological order:");
    for (int i = top - 1; i >= 0; i--)
        printf(" %d", stack[i]);
    printf("\n");
}

int main() {
    int n = 6;
    // Example graph edges (adjacency matrix)
    adj[5][2] = 1; adj[5][0] = 1;
    adj[4][0] = 1; adj[4][1] = 1;
    adj[2][3] = 1;
    adj[3][1] = 1;

    topologicalSort(n);
    return 0;
}
