#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

typedef struct Stack {
    Node* data[100];
    int top;
} Stack;

void push(Stack *s, Node *n) { s->data[++s->top] = n; }
Node* pop(Stack *s) { return s->top == -1 ? NULL : s->data[s->top--]; }
int empty(Stack *s) { return s->top == -1; }

void preorder(Node* root) {
    if (!root) return;
    Stack s; s.top = -1;
    push(&s, root);

    while (!empty(&s)) {
        Node *curr = pop(&s);
        printf("%d ", curr->data);
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
}

// Helper to create new nodes
Node* newNode(int val) {
    Node* n = malloc(sizeof(Node));
    n->data = val; n->left = n->right = NULL;
    return n;
}

int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    preorder(root);  // Output: 1 2 4 5 3
    return 0;
}
