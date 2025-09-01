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

void dequeue(){
    if(isEmpty()){
        printf("Queue Underflow!\n");
        return;
    }
    if(front==rear){
        free(front);
        front=rear=NULL;
    } else {
        Node* temp=front;
        front=front->next;
        rear->next=front; 
        free(temp);
    }
}

int peek(){
    if(isEmpty()){
        printf("Queue is Empty!\n");
        return -1;
    }
    return front->data;
}

void display(){
    if(isEmpty()){
        printf("Queue is Empty!\n");
        return;
    }
    Node* temp=front;
    printf("Queue: ");
    do{
        printf("%d ",temp->data);
        temp=temp->next;
    }while(temp!=front);
    printf("\n");
}
