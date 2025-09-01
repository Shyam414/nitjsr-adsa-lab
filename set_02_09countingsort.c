#include <stdio.h>

void countSort(int arr[], int n){
    int max = arr[0];
    for(int i=1; i<n;i++){
        if(arr[i]>max) max=arr[i];
    }
    int cou[max+1];
    for(int i=0; i<=max; i++){
        cou[i]=0;
    }
    for(int i=0;i<n;i++){
        cou[arr[i]]+=1;
    }
    int index=0;
    for(int i=0;i<=max;i++){
        while(cou[i]>0){
            arr[index++]=i;
            cou[i]--;
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

    countSort(arr, n);
    
    printf("Sorted array:   ");
    printArray(arr, n);

    return 0;
}