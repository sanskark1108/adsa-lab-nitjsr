#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 2 // Minimum degree

typedef struct BTreeNode {
    int keys[2 * T - 1], n;
    struct BTreeNode* C[2 * T];
    bool leaf;
} BTreeNode;

BTreeNode* createNode(bool leaf) {
    BTreeNode* node = malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    return node;
}

BTreeNode* createTree() {
    return createNode(true);
}

void deleteTree(BTreeNode* root) {
    if (!root) return;
    if (!root->leaf)
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->C[i]);
    free(root);
}

void traverse(BTreeNode* root) {
    for (int i = 0; i < root->n; i++) {
        if (!root->leaf) traverse(root->C[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) traverse(root->C[root->n]);
}

bool searchItem(BTreeNode* x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) i++;
    if (i < x->n && x->keys[i] == k) return true;
    return x->leaf ? false : searchItem(x->C[i], k);
}

void splitChild(BTreeNode* x, int i) {
    BTreeNode* z = createNode(x->C[i]->leaf);
    BTreeNode* y = x->C[i];
    z->n = T - 1;
    for (int j = 0; j < T - 1; j++) z->keys[j] = y->keys[j + T];
    if (!y->leaf)
        for (int j = 0; j < T; j++) z->C[j] = y->C[j + T];
    y->n = T - 1;
    for (int j = x->n; j >= i + 1; j--) x->C[j + 1] = x->C[j];
    x->C[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--) x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[T - 1];
    x->n++;
}

void insertNonFull(BTreeNode* x, int k) {
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
        if (x->C[i]->n == 2 * T - 1) {
            splitChild(x, i);
            if (k > x->keys[i]) i++;
        }
        insertNonFull(x->C[i], k);
    }
}

BTreeNode* insertItem(BTreeNode* root, int k) {
    if (root->n == 2 * T - 1) {
        BTreeNode* s = createNode(false);
        s->C[0] = root;
        splitChild(s, 0);
        insertNonFull(s, k);
        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

int getPred(BTreeNode* x) {
    while (!x->leaf) x = x->C[x->n];
    return x->keys[x->n - 1];
}

int getSucc(BTreeNode* x) {
    while (!x->leaf) x = x->C[0];
    return x->keys[0];
}

void merge(BTreeNode* x, int i) {
    BTreeNode *c1 = x->C[i], *c2 = x->C[i + 1];
    c1->keys[T - 1] = x->keys[i];
    for (int j = 0; j < c2->n; j++) c1->keys[j + T] = c2->keys[j];
    if (!c1->leaf)
        for (int j = 0; j <= c2->n; j++) c1->C[j + T] = c2->C[j];
    for (int j = i + 1; j < x->n; j++) {
        x->keys[j - 1] = x->keys[j];
        x->C[j] = x->C[j + 1];
    }
    c1->n += c2->n + 1;
    x->n--;
    free(c2);
}

void fill(BTreeNode* x, int i) {
    if (i && x->C[i - 1]->n >= T) {
        BTreeNode* c = x->C[i], *s = x->C[i - 1];
        for (int j = c->n - 1; j >= 0; j--) c->keys[j + 1] = c->keys[j];
        if (!c->leaf)
            for (int j = c->n; j >= 0; j--) c->C[j + 1] = c->C[j];
        c->keys[0] = x->keys[i - 1];
        if (!c->leaf) c->C[0] = s->C[s->n];
        x->keys[i - 1] = s->keys[s->n - 1];
        c->n++; s->n--;
    } else if (i < x->n && x->C[i + 1]->n >= T) {
        BTreeNode* c = x->C[i], *s = x->C[i + 1];
        c->keys[c->n++] = x->keys[i];
        if (!c->leaf) c->C[c->n] = s->C[0];
        x->keys[i] = s->keys[0];
        for (int j = 1; j < s->n; j++) s->keys[j - 1] = s->keys[j];
        if (!s->leaf)
            for (int j = 1; j <= s->n; j++) s->C[j - 1] = s->C[j];
        s->n--;
    } else {
        if (i < x->n) merge(x, i);
        else merge(x, i - 1);
    }
}

BTreeNode* deleteItem(BTreeNode* x, int k);

BTreeNode* removeFromNode(BTreeNode* x, int idx) {
    int k = x->keys[idx];
    if (x->leaf) {
        for (int i = idx + 1; i < x->n; i++) x->keys[i - 1] = x->keys[i];
        x->n--;
    } else {
        BTreeNode *pred = x->C[idx], *succ = x->C[idx + 1];
        if (pred->n >= T) {
            int p = getPred(pred);
            x->keys[idx] = p;
            x->C[idx] = deleteItem(pred, p);
        } else if (succ->n >= T) {
            int s = getSucc(succ);
            x->keys[idx] = s;
            x->C[idx + 1] = deleteItem(succ, s);
        } else {
            merge(x, idx);
            x->C[idx] = deleteItem(x->C[idx], k);
        }
    }
    return x;
}

BTreeNode* deleteItem(BTreeNode* x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) i++;
    if (i < x->n && x->keys[i] == k)
        return removeFromNode(x, i);
    if (x->leaf) return x;
    if (x->C[i]->n < T) fill(x, i);
    if (i > x->n) x->C[i - 1] = deleteItem(x->C[i - 1], k);
    else x->C[i] = deleteItem(x->C[i], k);
    return x;
}
int main() {
    BTreeNode* root = createTree();

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 5);
    root = insertItem(root, 6);
    root = insertItem(root, 12);
    root = insertItem(root, 30);
    root = insertItem(root, 7);
    root = insertItem(root, 17);

    printf("Before deletion:\n");
    traverse(root); printf("\n");

    root = deleteItem(root, 6);
    root = deleteItem(root, 13); // not in tree

    printf("After deletion:\n");
    traverse(root); printf("\n");

    printf("Search 17: %s\n", searchItem(root, 17) ? "Found" : "Not Found");

    deleteTree(root);
    return 0;
}

