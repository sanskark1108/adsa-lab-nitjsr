#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
typedef struct {
    int src, dest, weight;
} Edge;

// Structure to represent a graph
typedef struct {
    int V, E;      // Number of vertices and edges
    Edge* edges;   // Array of edges
} Graph;

// Structure for union-find
typedef struct {
    int parent;
    int rank;
} Subset;

// Function prototypes
Graph* createGraph(int V, int E);
int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);
int compareEdges(const void* a, const void* b);
void KruskalMST(Graph* graph);

int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges
    Graph* graph = createGraph(V, E);

    // add edges
    graph->edges[0].src = 0; graph->edges[0].dest = 1; graph->edges[0].weight = 10;
    graph->edges[1].src = 0; graph->edges[1].dest = 2; graph->edges[1].weight = 6;
    graph->edges[2].src = 0; graph->edges[2].dest = 3; graph->edges[2].weight = 5;
    graph->edges[3].src = 1; graph->edges[3].dest = 3; graph->edges[3].weight = 15;
    graph->edges[4].src = 2; graph->edges[4].dest = 3; graph->edges[4].weight = 4;

    KruskalMST(graph);

    free(graph->edges);
    free(graph);

    return 0;
}

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*) malloc(E * sizeof(Edge));
    return graph;
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);  // Path compression
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V]; // This will store the resultant MST
    int e = 0;      // Index for result[]
    int i = 0;      // Index for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edges, graph->E, sizeof(Edge), compareEdges);

    // Allocate memory for creating V subsets
    Subset *subsets = (Subset*) malloc(V * sizeof(Subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge
        Edge next_edge = graph->edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause cycle,
        // include it in result and increment the index of result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the edge
    }

    // Print the contents of result[] to display the MST
    printf("Following are the edges in the constructed MST\n");
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost Spanning Tree: %d\n", minimumCost);

    free(subsets);
}
