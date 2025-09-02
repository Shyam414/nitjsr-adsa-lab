#include<stdio.h>

void heapify(int arr[],int n,int i){
    int lar=i;
    int l=2*i+1;
    int r=2*i+2;
    if(arr[l]>arr[lar] && l<n) lar=l;
    if(arr[r]>arr[lar] && r<n) lar=r;
    if(lar!=i){
        int temp=arr[i];
        arr[i]=arr[lar];
        arr[lar]=temp;
        heapify(arr,n,lar);
    }
}

void heapSort(int arr[],int n){
    for(int i=n/2;i>=0;i--){
        heapify(arr,n,i);
    }
    for(int i=n-1;i>=0;i--){
        int temp=arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
        heapify(arr,i,0);
    }
}

void printArray(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}       

int main(){
    int arr[]={64,34,25,12,22,11,90};
    int n=sizeof(arr)/sizeof(arr[0]);
    printArray(arr,n);
    heapSort(arr,n);
    printArray(arr,n);
}