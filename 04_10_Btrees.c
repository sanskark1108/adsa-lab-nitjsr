#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 2
#define MAX (2*T - 1)

typedef struct BNode {
    int keys[MAX], n;
    struct BNode *C[MAX+1];
    bool leaf;
} BNode;

BNode* createTree() {
    BNode* x = malloc(sizeof(BNode));
    x->n = 0; x->leaf = true;
    return x;
}

void deleteTree(BNode* x) {
    if (!x) return;
    if (!x->leaf)
        for (int i = 0; i <= x->n; i++)
            deleteTree(x->C[i]);
    free(x);
}

bool searchItem(BNode* x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) i++;
    if (i < x->n && x->keys[i] == k) return true;
    return x->leaf ? false : searchItem(x->C[i], k);
}

void splitChild(BNode* x, int i) {
    BNode *y = x->C[i], *z = createTree();
    z->leaf = y->leaf; z->n = T - 1;
    for (int j = 0; j < T - 1; j++) z->keys[j] = y->keys[j + T];
    if (!y->leaf)
        for (int j = 0; j < T; j++) z->C[j] = y->C[j + T];
    y->n = T - 1;
    for (int j = x->n; j > i; j--) x->C[j + 1] = x->C[j];
    x->C[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--) x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[T - 1];
    x->n++;
}

void insertNonFull(BNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && x->keys[i] > k) i--;
        i++;
        if (x->C[i]->n == MAX) {
            splitChild(x, i);
            if (k > x->keys[i]) i++;
        }
        insertNonFull(x->C[i], k);
    }
}

BNode* insertItem(BNode* root, int k) {
    if (root->n == MAX) {
        BNode* s = createTree();
        s->leaf = false;
        s->C[0] = root;
        splitChild(s, 0);
        insertNonFull(s, k);
        return s;
    }
    insertNonFull(root, k);
    return root;
}

// Delete helpers (minimal, leaf only)
BNode* deleteItem(BNode* x, int k) {
    int i = 0;
    while (i < x->n && x->keys[i] < k) i++;
    if (x->leaf) {
        if (i < x->n && x->keys[i] == k) {
            for (; i < x->n - 1; i++) x->keys[i] = x->keys[i + 1];
            x->n--;
        }
        return x;
    }
    // Deletion in internal nodes omitted for brevity
    return x;
}
int main() {
    BNode* root = createTree();
    root = insertItem(root, 10);
    root = insertItem(root, 5);
    root = insertItem(root, 20);
    root = insertItem(root, 6);
    root = insertItem(root, 12);

    printf("Search 6: %s\n", searchItem(root, 6) ? "Found" : "Not Found");

    root = deleteItem(root, 6);
    printf("Search 6 after deletion: %s\n", searchItem(root, 6) ? "Found" : "Not Found");

    deleteTree(root);
    return 0;
}
