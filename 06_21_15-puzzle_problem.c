#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9,10,11,12},
    {13,14,15, 0}
};

int row[] = {1,-1,0,0}, col[] = {0,0,-1,1};

typedef struct Node {
    int mat[N][N], x, y, cost, level;
    struct Node* parent;
} Node;

int isSafe(int x, int y) { return x>=0 && x<N && y>=0 && y<N; }

int countMisplaced(int mat[N][N]) {
    int count = 0;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(mat[i][j] && mat[i][j] != goal[i][j]) count++;
    return count;
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    memcpy(node->mat, mat, sizeof(node->mat));
    int t = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = t;
    node->x = newX; node->y = newY;
    node->level = level; node->parent = parent;
    node->cost = countMisplaced(node->mat) + level;
    return node;
}

// Basic priority queue (array-based min-heap substitute)
Node* queue[10000]; int size = 0;

void push(Node* n) {
    queue[size++] = n;
    for(int i=size-1;i>0 && queue[i]->cost < queue[i-1]->cost;i--) {
        Node* t = queue[i]; queue[i] = queue[i-1]; queue[i-1] = t;
    }
}

Node* pop() { return queue[--size]; }

void printMatrix(int mat[N][N]) {
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++)
            printf(mat[i][j] ? "%2d " : " . ");
        printf("\n");
    }
    printf("\n");
}

void printPath(Node* n) {
    if (!n) return;
    printPath(n->parent);
    printMatrix(n->mat);
}

int isSolvable(int mat[N][N]) {
    int inv = 0, flat[N*N], k=0, rowWithZero;
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
        flat[k++] = mat[i][j];
        if (mat[i][j] == 0) rowWithZero = i;
    }
    for(int i=0;i<k-1;i++)
        for(int j=i+1;j<k;j++)
            if(flat[i] && flat[j] && flat[i] > flat[j]) inv++;
    return (inv + rowWithZero) % 2 == 0;
}

void solve(int initial[N][N], int x, int y) {
    if (!isSolvable(initial)) {
        printf("Unsolvable puzzle.\n"); return;
    }

    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    push(root);

    while (size > 0) {
        Node* min = pop();
        if (min->cost - min->level == 0) {
            printf("Solved in %d moves:\n\n", min->level);
            printPath(min); return;
        }

        for (int i=0;i<4;i++) {
            int nx = min->x + row[i], ny = min->y + col[i];
            if (isSafe(nx, ny)) push(newNode(min->mat, min->x, min->y, nx, ny, min->level+1, min));
        }
    }
}

int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9,10,7,12},
        {13,14,11,15}
    };
    int x, y;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if (initial[i][j] == 0) { x = i; y = j; }

    solve(initial, x, y);
    return 0;
}
