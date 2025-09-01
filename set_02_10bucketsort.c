#include <stdio.h>

void insertionSortFloat(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];      
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}
void bucketSort(float arr[], int n){
    float* b[n];
    int count[n];
    for(int i=0;i<n;i++) count[i]=0;
    for(int i=0;i<n;i++){
        int bi = n*arr[i];
        b[bi][count[bi]++] = arr[i];
    }
    for(int i=0;i<n;i++)
        if(count[i]>1) insertionSortFloat(b[i], count[i]);
    int index=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<count[i];j++)
            arr[index++]=b[i][j];
}

void printArray(float arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%.3f ", arr[i]);
    printf("\n");
}

int main() {
    float arr[]={0.64, 0.34, 0.25, 0.12, 0.22, 0.11, 0.90,0.803,0.105};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    bucketSort(arr, n);
    
    printf("Sorted array:   ");
    printArray(arr, n);

    return 0;
}