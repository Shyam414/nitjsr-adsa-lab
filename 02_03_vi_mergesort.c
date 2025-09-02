#include<stdio.h>

void merge(int arr[], int low, int mid, int up){
    int n1=mid-low+1;
    int n2=up-mid;
    int L[n1], R[n2];
    for(int i =0;i<n1;i++) L[i]=arr[low+i];
    for(int j =0;j<n2;j++) R[j]=arr[mid+1+j];
    int k=low;
    int l=0;
    int r=0;
    while(l<n1 && r<n2){
        if(L[l]>R[r]) arr[k++]=R[r++];
        else arr[k++]=L[l++];
    }
    while(l<n1){
        arr[k++]=L[l++];
    }
    while(r<n2){
        arr[k++]=R[r++];
    }

}

void mergeSort(int arr[],int l,int h){
    if(l<h){
        int mid=l+(h-l)/2;
        mergeSort(arr,l,mid);
        mergeSort(arr,mid+1,h);
        merge(arr,l,mid,h);
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
    mergeSort(arr,0,n-1);
    printArray(arr,n);
}