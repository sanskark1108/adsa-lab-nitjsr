#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node *left, *right, *parent;
} Node;

Node *NIL;

Node* createNode(int key) {
    Node* n = malloc(sizeof(Node));
    n->key = key; n->color = RED;
    n->left = n->right = n->parent = NIL;
    return n;
}

Node* createTree() {
    NIL = malloc(sizeof(Node));
    NIL->color = BLACK;
    return NIL;
}

void leftRotate(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(Node **root, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void insertFixup(Node **root, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) { z = z->parent; leftRotate(root, z); }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) { z = z->parent; rightRotate(root, z); }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

Node* insertItem(Node *root, int key) {
    Node *z = createNode(key), *y = NIL, *x = root;
    while (x != NIL) { y = x; x = key < x->key ? x->left : x->right; }
    z->parent = y;
    if (y == NIL) root = z;
    else if (key < y->key) y->left = z;
    else y->right = z;
    z->left = z->right = NIL;
    insertFixup(&root, z);
    return root;
}

Node* searchItem(Node* root, int key) {
    while (root != NIL && root->key != key)
        root = (key < root->key) ? root->left : root->right;
    return root;
}

void transplant(Node **root, Node *u, Node *v) {
    if (u->parent == NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

Node* minNode(Node *x) {
    while (x->left != NIL) x = x->left;
    return x;
}

void deleteFixup(Node **root, Node *x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK; x->parent->color = RED;
                leftRotate(root, x->parent); w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED; x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK; w->color = RED;
                    rightRotate(root, w); w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK; w->right->color = BLACK;
                leftRotate(root, x->parent); x = *root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK; x->parent->color = RED;
                rightRotate(root, x->parent); w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED; x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK; w->color = RED;
                    leftRotate(root, w); w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK; w->left->color = BLACK;
                rightRotate(root, x->parent); x = *root;
            }
        }
    }
    x->color = BLACK;
}

Node* deleteItem(Node* root, int key) {
    Node *z = searchItem(root, key);
    if (z == NIL) return root;

    Node *y = z, *x;
    Color orig = y->color;

    if (z->left == NIL) { x = z->right; transplant(&root, z, z->right); }
    else if (z->right == NIL) { x = z->left; transplant(&root, z, z->left); }
    else {
        y = minNode(z->right);
        orig = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            transplant(&root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(&root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);
    if (orig == BLACK) deleteFixup(&root, x);
    return root;
}

void deleteTree(Node* root) {
    if (root == NIL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}
int main() {
    Node *root = createTree();

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 5);
    root = deleteItem(root, 10);

    Node* found = searchItem(root, 5);
    if (found != NIL) printf("Found: %d\n", found->key);

    deleteTree(root);
    free(NIL);  // Don't forget to free sentinel
    return 0;
}
