#include <stdio.h>
#include <stdlib.h>

#define N 7
typedef struct Node {float val; struct Node *next;} Node;

void insertionSort(Node **bucket) {
    Node *sorted = NULL;
    while(*bucket) {
        Node *curr = *bucket, *next = curr->next;
        if(!sorted || curr->val < sorted->val) {
            curr->next = sorted;
            sorted = curr;
        } else {
            Node *p = sorted;
            while(p->next && p->next->val < curr->val) p=p->next;
            curr->next = p->next;
            p->next = curr;
        }
        *bucket = next;
    }
    *bucket = sorted;
}

void bucketSort(float arr[], int n) {
    Node *buckets[n];
    for(int i=0; i<n; i++) buckets[i] = NULL;
    for(int i=0; i<n; i++) {
        int idx = (int)(arr[i]*n);
        Node *node = malloc(sizeof(Node));
        node->val = arr[i];
        node->next = buckets[idx];
        buckets[idx] = node;
    }
    for(int i=0; i<n; i++) insertionSort(&buckets[i]);
    int idx=0;
    for(int i=0; i<n; i++) {
        Node *p = buckets[i];
        while(p) {
            arr[idx++] = p->val;
            Node *tmp = p; p=p->next; free(tmp);
        }
    }
}

int main() {
    float arr[N] = {0.42,0.32,0.23,0.52,0.25,0.47,0.51};
    bucketSort(arr,N);
    for(int i=0;i<N;i++) printf("%f ", arr[i]);
    return 0;
}
