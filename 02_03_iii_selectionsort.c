#include<stdio.h>

void selectionSort(int arr[],int n){
    for(int i=0; i<n-1;i++){
        int minid=i;
        for(int j=i+1; j<n;j++){
            if(arr[j]<arr[minid]){
                minid=j;
            }
        }
        
        int temp=arr[i];
        arr[i]=arr[minid];
        arr[minid]=temp;
        
    }
}

void printArray(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[]={12,11,13,5,6};
    int n=sizeof(arr)/sizeof(arr[0]);
    printArray(arr,n);
    selectionSort(arr,n);
    printArray(arr,n);
}