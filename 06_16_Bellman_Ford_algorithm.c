#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// A structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// Function to print the distance array
void printDistances(int dist[], int V) {
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d\t%d\n", i, dist[i]);
}

// Bellman-Ford algorithm
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = graph->edge[j].src;
        int v = graph->edge[j].dest;
        int weight = graph->edge[j].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printDistances(dist, V);
}

// Example usage
int main() {
    int V = 5; // Number of vertices
    int E = 8; // Number of edges
    struct Graph* graph = createGraph(V, E);

    // Add edges
    graph->edge[0] = (struct Edge){0, 1, -1};
    graph->edge[1] = (struct Edge){0, 2, 4};
    graph->edge[2] = (struct Edge){1, 2, 3};
    graph->edge[3] = (struct Edge){1, 3, 2};
    graph->edge[4] = (struct Edge){1, 4, 2};
    graph->edge[5] = (struct Edge){3, 2, 5};
    graph->edge[6] = (struct Edge){3, 1, 1};
    graph->edge[7] = (struct Edge){4, 3, -3};

    BellmanFord(graph, 0);

    free(graph->edge);
    free(graph);

    return 0;
}
