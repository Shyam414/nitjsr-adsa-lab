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

int main(){
    int choice, value;
    while(1){
        printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d",&value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                value=peek();
                if(value!=-1)
                    printf("Front element: %d\n",value);
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}