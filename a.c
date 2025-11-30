#include<stdio.h>

void insertion(int arr [],int n){
    for(int i=1;i<n;i++){
        int key=arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void bubble(int arr[],int n){
    int i=n-1;
    while(i>0){
        for(int j=1;j<=i;j++){
            if(arr[j]<arr[j-1]){
                arr[j]=arr[j]^arr[j-1];
                arr[j-1]=arr[j]^arr[j-1];
                arr[j]=arr[j]^arr[j-1];
            }
        }
        i--;
    }
}