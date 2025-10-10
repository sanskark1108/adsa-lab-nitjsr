#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];   // Adjacency matrix
int color[MAX];        // Color array: -1 = unvisited, 0 and 1 = colors
int queue[MAX];
int front = 0, rear = 0;
int n;  // number of vertices

void enqueue(int v) {
    queue[rear++] = v;
}

int dequeue() {
    return queue[front++];
}

bool isEmpty() {
    return front == rear;
}

bool bfsCheckBipartite(int start) {
    color[start] = 0;
    enqueue(start);

    while (!isEmpty()) {
        int u = dequeue();

        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {  // there's an edge
                if (color[v] == -1) {
                    // Assign alternate color
                    color[v] = 1 - color[u];
                    enqueue(v);
                } else if (color[v] == color[u]) {
                    // Same color on both ends — not bipartite
                    return false;
                }
            }
        }
    }
    return true;
}

bool isBipartite() {
    for (int i = 0; i < n; i++)
        color[i] = -1;

    // The graph might be disconnected
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (!bfsCheckBipartite(i))
                return false;
        }
    }
    return true;
}

int main() {
    int e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v), 0-indexed:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  // Undirected graph
    }

    if (isBipartite())
        printf("The graph is bipartite.\n");
    else
        printf("The graph is NOT bipartite.\n");

    return 0;
}
