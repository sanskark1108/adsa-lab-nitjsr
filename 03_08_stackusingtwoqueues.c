#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    int data[SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return (q->rear + 1) % SIZE == q->front;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % SIZE;
    }
    q->data[q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int val = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % SIZE;
    }
    return val;
}

int front(Queue *q) {
    if (!isEmpty(q))
        return q->data[q->front];
    return -1;
}
typedef struct {
    Queue q1, q2;
} Stack1;

void initStack1(Stack1 *s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

void push1(Stack1 *s, int x) {
    enqueue(&s->q2, x);
    while (!isEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }
    // Swap q1 and q2
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

int pop1(Stack1 *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return dequeue(&s->q1);
}

int top1(Stack1 *s) {
    return front(&s->q1);
}
typedef struct {
    Queue q1, q2;
} Stack2;

void initStack2(Stack2 *s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

void push2(Stack2 *s, int x) {
    enqueue(&s->q1, x);
}

int pop2(Stack2 *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is empty!\n");
        return -1;
    }
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }
    int val = dequeue(&s->q1);
    // Swap q1 and q2
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
    return val;
}

int top2(Stack2 *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is empty!\n");
        return -1;
    }
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }
    int val = front(&s->q1);
    enqueue(&s->q2, dequeue(&s->q1));
    // Swap q1 and q2
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
    return val;
}
int main() {
    Stack1 s1;
    Stack2 s2;

    printf("Testing Method 1 (Enqueue Costly):\n");
    initStack1(&s1);
    push1(&s1, 10);
    push1(&s1, 20);
    push1(&s1, 30);
    printf("Top: %d\n", top1(&s1));
    printf("Pop: %d\n", pop1(&s1));
    printf("Top: %d\n", top1(&s1));

    printf("\nTesting Method 2 (Dequeue Costly):\n");
    initStack2(&s2);
    push2(&s2, 100);
    push2(&s2, 200);
    push2(&s2, 300);
    printf("Top: %d\n", top2(&s2));
    printf("Pop: %d\n", pop2(&s2));
    printf("Top: %d\n", top2(&s2));

    return 0;
}
