#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX];
int path[MAX];
int n;  // number of vertices

// Function to check if vertex v can be added at index pos in the Hamiltonian Cycle
bool isSafe(int v, int pos) {
    // Check if this vertex is adjacent to the previous vertex
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if the vertex has already been included
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive function to find Hamiltonian Cycle
bool hamiltonianCycleUtil(int pos) {
    if (pos == n) {
        // If last vertex is adjacent to the first, a cycle is formed
        return graph[path[pos - 1]][path[0]] == 1;
    }

    // Try different vertices as candidates
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamiltonianCycleUtil(pos + 1))
                return true;

            // Backtrack
            path[pos] = -1;
        }
    }
    return false;
}

// Function to solve the Hamiltonian Cycle problem
bool hasHamiltonianCycle() {
    for (int i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0;  // Start at vertex 0

    return hamiltonianCycleUtil(1);
}

int main() {
    int e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize the graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v) format, 0-indexed:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  // Since it's an undirected graph
    }

    if (hasHamiltonianCycle())
        printf("Hamiltonian Cycle exists.\n");
    else
        printf("No Hamiltonian Cycle exists.\n");

    return 0;
}

