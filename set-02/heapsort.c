#include <stdio.h>

void maxHeap(int arr[], int n, int i){
    int lar=i;
    int l=2*i+1;
    int r=2*i+2;
    if (l<n && arr[l]>arr[lar]){
        lar=l;
    }
    if (r<n && arr[r]>arr[lar]){
        lar=r;
    }
    if(lar!=i){
        int temp=arr[i];
        arr[i]=arr[lar];
        arr[lar]=temp;
        maxHeap(arr, n, lar);
    }
}

void heapSort(int arr[], int n){
    //build max heap
    for(int i=n/2-1; i>=0; i--){
        maxHeap(arr, n, i);
    }
    //one by one extract elements from heap
    for(int i=n-1; i>0; i--){
        int temp=arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
        maxHeap(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[]={64, 34, 25, 12, 22, 11, 90,803,105};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    heapSort(arr, n);
    
    printf("Sorted array:   ");
    printArray(arr, n);

    return 0;
}