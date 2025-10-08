#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

//------------------- SCC (Tarjan) for Directed Graph -------------------

int timeSCC, sccCount;
int discSCC[MAX], lowSCC[MAX], stackSCC[MAX], inStackSCC[MAX];
int topSCC;

void dfsSCC(int u, int adj[][MAX], int n) {
    discSCC[u] = lowSCC[u] = ++timeSCC;
    stackSCC[topSCC++] = u; inStackSCC[u] = 1;
    for (int v = 0; v < n; v++) {
        if (!adj[u][v]) continue;
        if (!discSCC[v]) {
            dfsSCC(v, adj, n);
            if (lowSCC[v] < lowSCC[u]) lowSCC[u] = lowSCC[v];
        } else if (inStackSCC[v] && discSCC[v] < lowSCC[u]) {
            lowSCC[u] = discSCC[v];
        }
    }
    if (lowSCC[u] == discSCC[u]) {
        printf("SCC %d:", ++sccCount);
        int w;
        do {
            w = stackSCC[--topSCC];
            inStackSCC[w] = 0;
            printf(" %d", w);
        } while (w != u);
        printf("\n");
    }
}

//---------------- BCC, Articulation Points, Bridges for Undirected Graph ------------------

int timeBCC, apCount, bridgeCount;
int discBCC[MAX], lowBCC[MAX], parentBCC[MAX], visitedBCC[MAX], ap[MAX];
int adjUndir[MAX][MAX];

void dfsBCC(int u, int n) {
    discBCC[u] = lowBCC[u] = ++timeBCC;
    visitedBCC[u] = 1;
    int children = 0;
    for (int v = 0; v < n; v++) {
        if (!adjUndir[u][v]) continue;
        if (!visitedBCC[v]) {
            children++;
            parentBCC[v] = u;
            dfsBCC(v, n);
            if (lowBCC[v] < lowBCC[u]) lowBCC[u] = lowBCC[v];

            // Articulation point
            if ((parentBCC[u] == -1 && children > 1) || (parentBCC[u] != -1 && lowBCC[v] >= discBCC[u]))
                ap[u] = 1;

            // Bridge
            if (lowBCC[v] > discBCC[u]) {
                printf("Bridge between %d - %d\n", u, v);
                bridgeCount++;
            }
        } else if (v != parentBCC[u] && discBCC[v] < lowBCC[u]) {
            lowBCC[u] = discBCC[v];
        }
    }
}

void findAPandBridges(int n) {
    for (int i = 0; i < n; i++) {
        discBCC[i] = lowBCC[i] = parentBCC[i] = visitedBCC[i] = ap[i] = 0;
    }
    timeBCC = bridgeCount = apCount = 0;
    for (int i = 0; i < n; i++) {
        parentBCC[i] = -1;
        if (!visitedBCC[i]) dfsBCC(i, n);
    }
    printf("Articulation Points:");
    for (int i = 0; i < n; i++)
        if (ap[i]) { printf(" %d", i); apCount++; }
    printf("\n");
}

//-------------------- Main --------------------

int main() {
    int n = 5; // Number of nodes

    // Directed graph adjacency matrix for SCC (example)
    int adj[MAX][MAX] = {0};
    adj[0][2] = adj[2][1] = adj[1][0] = adj[0][3] = adj[3][4] = 1;

    printf("Strongly Connected Components:\n");
    for (int i = 0; i < n; i++) discSCC[i] = lowSCC[i] = inStackSCC[i] = 0;
    timeSCC = topSCC = sccCount = 0;
    for (int i = 0; i < n; i++)
        if (!discSCC[i]) dfsSCC(i, adj, n);

    // Undirected graph adjacency matrix for BCC, AP, Bridges (example)
    // Example: edges: 0-1,0-2,1-2,1-3,3-4
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjUndir[i][j] = 0;

    adjUndir[0][1] = adjUndir[1][0] = 1;
    adjUndir[0][2] = adjUndir[2][0] = 1;
    adjUndir[1][2] = adjUndir[2][1] = 1;
    adjUndir[1][3] = adjUndir[3][1] = 1;
    adjUndir[3][4] = adjUndir[4][3] = 1;

    findAPandBridges(n);

    return 0;
}
