include <stdio.h>
#include <stdlib.h>

typedef struct { int l, r, phase; } Frame;

void merge(int *a, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1*sizeof(int)), *R = malloc(n2*sizeof(int));
    for(int i=0;i<n1;i++) L[i]=a[l+i];
    for(int i=0;i<n2;i++) R[i]=a[m+1+i];
    int i=0,j=0,k=l;
    while(i<n1 && j<n2) a[k++] = (L[i]<=R[j]) ? L[i++] : R[j++];
    while(i<n1) a[k++] = L[i++];
    while(j<n2) a[k++] = R[j++];
    free(L); free(R);
}

void mergeSort(int *a, int n) {
    Frame stack[64];
    int top = 0;
    stack[top++] = (Frame){0, n-1, 0};
    while(top) {
        Frame *f = &stack[top-1];
        int l = f->l, r = f->r, phase = f->phase;
        if(l >= r) { top--; continue; }
        int m = (l+r)/2;
        if(phase == 0) {
            f->phase = 1;
            stack[top++] = (Frame){l, m, 0};
        } else if(phase == 1) {
            f->phase = 2;
            stack[top++] = (Frame){m+1, r, 0};
        } else {
            merge(a, l, m, r);
            top--;
        }
    }
}

int main() {
    int a[] = {4,2,4,5,1,3,2,6}, n=8;
    mergeSort(a,n);
    for(int i=0;i<n;i++) printf("%d ", a[i]);
    return 0;
}
