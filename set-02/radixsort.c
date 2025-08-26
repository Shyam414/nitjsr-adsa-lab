#include <stdio.h>

void radixSort(int arr[], int n){
    int max = arr[0];
    for(int i=1; i<n;i++){
        if(arr[i]>max) max=arr[i];
    }
    for(int exp=1; max/exp>0; exp*=10){
        int output[n];
        int count[10]={0};
        for(int i=0;i<n;i++){
            count[(arr[i]/exp)%10]++;
        }
        for(int i=1;i<10;i++){
            count[i]+=count[i-1];
        }
        for(int i=n-1;i>=0;i--){
            output[count[(arr[i]/exp)%10]-1]=arr[i];
            count[(arr[i]/exp)%10]--;
        }
        for(int i=0;i<n;i++){
            arr[i]=output[i];
        }
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

    radixSort(arr, n);
    
    printf("Sorted array:   ");
    printArray(arr, n);

    return 0;
}