#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef enum { WHITE, GRAY, BLACK } Color;

typedef struct {
    int n;                      // number of vertices
    int adj[MAX_VERTICES][MAX_VERTICES];  // adjacency matrix
} Graph;

Color color[MAX_VERTICES];
int discovery_time[MAX_VERTICES];
int finish_time[MAX_VERTICES];
int time;

void dfs_visit(Graph *g, int u) {
    color[u] = GRAY;
    discovery_time[u] = ++time;

    for (int v = 0; v < g->n; v++) {
        if (g->adj[u][v]) {
            if (color[v] == WHITE) {
                printf("Tree Edge: (%d -> %d)\n", u, v);
                dfs_visit(g, v);
            } else if (color[v] == GRAY) {
                printf("Back Edge: (%d -> %d)\n", u, v);
            } else if (color[v] == BLACK) {
                if (discovery_time[u] < discovery_time[v]) {
                    printf("Forward Edge: (%d -> %d)\n", u, v);
                } else {
                    printf("Cross Edge: (%d -> %d)\n", u, v);
                }
            }
        }
    }

    color[u] = BLACK;
    finish_time[u] = ++time;
}

void dfs(Graph *g) {
    for (int i = 0; i < g->n; i++) {
        color[i] = WHITE;
        discovery_time[i] = 0;
        finish_time[i] = 0;
    }
    time = 0;

    for (int i = 0; i < g->n; i++) {
        if (color[i] == WHITE) {
            dfs_visit(g, i);
        }
    }
}

int main() {
    Graph g;
    g.n = 6;

    // Initialize adjacency matrix with zeros
    for (int i = 0; i < g.n; i++)
        for (int j = 0; j < g.n; j++)
            g.adj[i][j] = 0;

    // Example directed graph edges
    g.adj[0][1] = 1;
    g.adj[0][2] = 1;
    g.adj[1][2] = 1;
    g.adj[2][0] = 1;
    g.adj[2][3] = 1;
    g.adj[3][3] = 1;
    g.adj[4][5] = 1;

    dfs(&g);

    return 0;
}
