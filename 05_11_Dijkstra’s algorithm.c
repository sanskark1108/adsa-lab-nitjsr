#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5  // Number of vertices (can be changed)

// Find the vertex with the minimum distance value, from
// the set of vertices not yet processed
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Print the constructed distance array
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Dijkstra's algorithm function
void dijkstra(int graph[V][V], int src) {
    int dist[V];      // Output array: dist[i] holds shortest distance from src to i
    bool sptSet[V];   // sptSet[i] will be true if vertex i is in shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;  // Distance of source vertex from itself is always 0

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;  // Mark the chosen vertex as processed

        // Update distance value of the adjacent vertices of the chosen vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if it's not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the result
    printSolution(dist);
}

// Driver code
int main() {
    // Example graph represented using adjacency matrix
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}
    };

    int source = 0;
    dijkstra(graph, source);

    return 0;
}
