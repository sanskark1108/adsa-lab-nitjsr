#include <stdio.h>
#include <stdlib.h>

typedef struct N {
    int k, h;
    struct N *l, *r;
} N;

int h(N* n) { return n ? n->h : 0; }
int max(int a, int b) { return a > b ? a : b; }

N* newN(int k) {
    N* n = malloc(sizeof(N));
    n->k = k; n->l = n->r = NULL; n->h = 1;
    return n;
}

N* rotR(N* y) {
    N* x = y->l, *T = x->r;
    x->r = y; y->l = T;
    y->h = max(h(y->l), h(y->r)) + 1;
    x->h = max(h(x->l), h(x->r)) + 1;
    return x;
}

N* rotL(N* x) {
    N* y = x->r, *T = y->l;
    y->l = x; x->r = T;
    x->h = max(h(x->l), h(x->r)) + 1;
    y->h = max(h(y->l), h(y->r)) + 1;
    return y;
}

int bal(N* n) { return h(n->l) - h(n->r); }

N* insertItem(N* n, int k) {
    if (!n) return newN(k);
    if (k < n->k) n->l = insertItem(n->l, k);
    else if (k > n->k) n->r = insertItem(n->r, k);
    else return n;

    n->h = 1 + max(h(n->l), h(n->r));
    int b = bal(n);

    if (b > 1 && k < n->l->k) return rotR(n);
    if (b < -1 && k > n->r->k) return rotL(n);
    if (b > 1 && k > n->l->k) { n->l = rotL(n->l); return rotR(n); }
    if (b < -1 && k < n->r->k) { n->r = rotR(n->r); return rotL(n); }

    return n;
}

N* minN(N* n) {
    while (n->l) n = n->l;
    return n;
}

N* deleteItem(N* r, int k) {
    if (!r) return r;
    if (k < r->k) r->l = deleteItem(r->l, k);
    else if (k > r->k) r->r = deleteItem(r->r, k);
    else {
        if (!r->l || !r->r) {
            N* t = r->l ? r->l : r->r;
            if (!t) { free(r); return NULL; }
            *r = *t; free(t);
        } else {
            N* t = minN(r->r);
            r->k = t->k;
            r->r = deleteItem(r->r, t->k);
        }
    }
    r->h = 1 + max(h(r->l), h(r->r));
    int b = bal(r);

    if (b > 1 && bal(r->l) >= 0) return rotR(r);
    if (b > 1 && bal(r->l) < 0) { r->l = rotL(r->l); return rotR(r); }
    if (b < -1 && bal(r->r) <= 0) return rotL(r);
    if (b < -1 && bal(r->r) > 0) { r->r = rotR(r->r); return rotL(r); }

    return r;
}

N* searchItem(N* r, int k) {
    if (!r || r->k == k) return r;
    return k < r->k ? searchItem(r->l, k) : searchItem(r->r, k);
}

void deleteTree(N* r) {
    if (!r) return;
    deleteTree(r->l); deleteTree(r->r);
    free(r);
}

N* createTree() { return NULL; }
int main() {
    N* tree = createTree();

    tree = insertItem(tree, 10);
    tree = insertItem(tree, 20);
    tree = insertItem(tree, 5);

    if (searchItem(tree, 10))
        printf("Found 10\n");

    tree = deleteItem(tree, 10);

    deleteTree(tree);
    return 0;
}
