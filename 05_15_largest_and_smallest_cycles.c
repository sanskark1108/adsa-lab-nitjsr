#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_CYCLE_LENGTH 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* head[MAX_VERTICES];
    int numVertices;
    int isDirected; // 0 for undirected, 1 for directed
} Graph;

int visited[MAX_VERTICES];
int path[MAX_VERTICES];
int pathLen;

int minCycle[MAX_CYCLE_LENGTH];
int maxCycle[MAX_CYCLE_LENGTH];
int minCycleLen = MAX_CYCLE_LENGTH;
int maxCycleLen = 0;

// Function to create a new node
Node* createNode(int v) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Initialize the graph
void initGraph(Graph* g, int vertices, int isDirected) {
    g->numVertices = vertices;
    g->isDirected = isDirected;
    for (int i = 0; i < vertices; i++) {
        g->head[i] = NULL;
    }
}

// Add edge
void addEdge(Graph* g, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = g->head[src];
    g->head[src] = newNode;

    if (!g->isDirected) {
        Node* newNode2 = createNode(src);
        newNode2->next = g->head[dest];
        g->head[dest] = newNode2;
    }
}

// Utility to check if cycle already exists (avoid duplicates)
int isInPath(int v) {
    for (int i = 0; i < pathLen; i++) {
        if (path[i] == v) return i;
    }
    return -1;
}

// DFS to find all cycles
void dfs(Graph* g, int start, int current) {
    visited[current] = 1;
    path[pathLen++] = current;

    Node* temp = g->head[current];
    while (temp != NULL) {
        int idx = isInPath(temp->vertex);
        if (idx != -1 && temp->vertex == start && pathLen > 2) {
            // Found a cycle
            if (pathLen < minCycleLen) {
                minCycleLen = pathLen;
                memcpy(minCycle, path, sizeof(int) * pathLen);
            }
            if (pathLen > maxCycleLen) {
                maxCycleLen = pathLen;
                memcpy(maxCycle, path, sizeof(int) * pathLen);
            }
        } else if (!visited[temp->vertex]) {
            dfs(g, start, temp->vertex);
        }
        temp = temp->next;
    }

    visited[current] = 0;
    pathLen--;
}

// Wrapper to find all cycles
void findCycles(Graph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        memset(visited, 0, sizeof(visited));
        pathLen = 0;
        dfs(g, i, i);
    }

    if (minCycleLen == MAX_CYCLE_LENGTH) {
        printf("No cycles found.\n");
    } else {
        printf("Smallest cycle (length %d): ", minCycleLen);
        for (int i = 0; i < minCycleLen; i++) {
            printf("%d ", minCycle[i]);
        }
        printf("\n");

        printf("Largest cycle (length %d): ", maxCycleLen);
        for (int i = 0; i < maxCycleLen; i++) {
            printf("%d ", maxCycle[i]);
        }
        printf("\n");
    }
}

// Main function for testing
int main() {
    Graph g;
    initGraph(&g, 6, 1); // 1 for directed graph, 0 for undirected

    // Add edges (modify as needed)
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 0);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 4);
    addEdge(&g, 4, 5);
    addEdge(&g, 5, 3);

    findCycles(&g);

    return 0;
}
