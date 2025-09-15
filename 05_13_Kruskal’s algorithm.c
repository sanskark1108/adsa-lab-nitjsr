#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent an edge
typedef struct {
    int u, v;
    int weight;
} Edge;

// Structure to represent a graph
typedef struct {
    int V, E;
    Edge edges[MAX];
} Graph;

// Structure for disjoint set (for union-find)
int parent[MAX];

// Function to find the set of an element i (with path compression)
int find(int i) {
    if (parent[i] == -1)
        return i;
    return parent[i] = find(parent[i]);
}

// Union of two sets x and y
void union_sets(int x, int y) {
    int xset = find(x);
    int yset = find(y);
    if (xset != yset)
        parent[xset] = yset;
}

// Comparator function to sort edges by weight
int compare(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

// Kruskal's algorithm
void kruskalMST(Graph* g) {
    int i, e = 0;
    int mst_weight = 0;

    // Initialize disjoint sets
    for (i = 0; i < g->V; i++)
        parent[i] = -1;

    // Sort edges by weight
    qsort(g->edges, g->E, sizeof(Edge), compare);

    printf("Edges in the Minimum Spanning Tree:\n");

    for (i = 0; i < g->E && e < g->V - 1; i++) {
        Edge next = g->edges[i];
        int set_u = find(next.u);
        int set_v = find(next.v);

        // If including this edge doesn't cause a cycle
        if (set_u != set_v) {
            printf("%d -- %d == %d\n", next.u, next.v, next.weight);
            mst_weight += next.weight;
            union_sets(set_u, set_v);
            e++;
        }
    }

    printf("Total weight of MST: %d\n", mst_weight);
}

// Example usage
int main() {
    Graph g;
    int i;

    // Example graph input
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &g.V, &g.E);

    printf("Enter each edge in format: u v weight\n");
    for (i = 0; i < g.E; i++) {
        scanf("%d %d %d", &g.edges[i].u, &g.edges[i].v, &g.edges[i].weight);
    }

    kruskalMST(&g);

    return 0;
}
