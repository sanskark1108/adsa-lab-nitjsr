#include <stdio.h>

void radixExchangeSort(int *a, int left, int right, int bit) {
    if(left >= right || bit < 0) return;
    int i=left, j=right;
    while(i <= j) {
        while(i <= j && !(a[i] & (1 << bit))) i++;
        while(i <= j && (a[j] & (1 << bit))) j--;
        if(i < j) {int t=a[i]; a[i]=a[j]; a[j]=t; i++; j--;}
    }
    radixExchangeSort(a,left,j,bit-1);
    radixExchangeSort(a,i,right,bit-1);
}

int main() {
    int a[] = {4,2,7,1,3,6,5}, n=7;
    radixExchangeSort(a,0,n-1,31);
    for(int i=0; i<n; i++) printf("%d ", a[i]);
    return 0;
}
