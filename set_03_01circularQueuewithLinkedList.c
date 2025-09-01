#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

Node* front=NULL;
Node* rear=NULL;

int isEmpty(){
    return front==NULL;
}

void enqueue(int x){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=x;
    newNode->next=NULL;
    if(isEmpty()){
        front=rear=newNode;
        rear->next=front; 
    } else {
        rear->next=newNode;
        rear=newNode;
        rear->next=front; 
    }
}