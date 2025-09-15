#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5  // Number of vertices in the graph (change as needed)

// Function to find the vertex with the minimum key value that is not yet included in MST
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the constructed MST stored in parent[]
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and print MST for a graph represented using adjacency matrix
void primMST(int graph[V][V]) {
    int parent[V];   // Array to store constructed MST
    int key[V];      // Key values to pick minimum weight edge in cut
    bool mstSet[V];  // To represent set of vertices included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Start from the first vertex
    key[0] = 0;      // Make key 0 so that this vertex is picked first
    parent[0] = -1;  // First node is always the root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);  // Pick the min key vertex
        mstSet[u] = true;             // Add the picked vertex to MST set

        // Update key and parent of the adjacent vertices
        for (int v = 0; v < V; v++) {
            // Update only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph);
}

// Driver code
int main() {
    // Example graph (change values as needed)
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    primMST(graph);

    return 0;
}
