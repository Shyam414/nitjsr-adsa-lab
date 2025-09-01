#include <stdio.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int st = low;
    int en=high;
    while(st<en){
        while(arr[st]<=pivot){
            st++;
        }
        while(arr[en]>pivot){
            en--;
        }
        if(st<en){
            int temp = arr[st];
            arr[st] = arr[en];
            arr[en] = temp;
        }
    }
    arr[low] = arr[en];
    arr[en] = pivot;
    return en;  
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
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

    quickSort(arr, 0, n-1);
    
    printf("Sorted array:   ");
    printArray(arr, n);

    return 0;
}