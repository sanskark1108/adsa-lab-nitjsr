#include <stdio.h>
#include <string.h>

void countingSort(int arr[], int n, int max) {
    int count[max+1], output[n];
    memset(count, 0, sizeof(count));
    for(int i=0; i<n; i++) count[arr[i]]++;
    for(int i=1; i<=max; i++) count[i]+=count[i-1];
    for(int i=n-1; i>=0; i--) output[--count[arr[i]]] = arr[i];
    for(int i=0; i<n; i++) arr[i] = output[i];
}

int main() {
    int arr[] = {4,2,2,8,3,3,1}, n=7, max=8;
    countingSort(arr,n,max);
    for(int i=0;i<n;i++) printf("%d ",arr[i]);
    return 0;
}
