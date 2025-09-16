#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node *left, *right;
}Node;

Node* createNode(int data){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=data;
    newNode->left=newNode->right=NULL;
    return newNode;
}

#define Max 100
typedef struct{
    Node* arr[Max];
    int top;
}stack;

void initStack(stack* s){
    s->top=-1;
}

int isEmpty(stack* s){
    return s->top==-1;
}

void push(stack* s, Node* node ){
    s->arr[++s->top]=node;
}

Node* pop(stack* s){
    return s->arr[s->top--];
}

void preorder(Node* root){
    if(root==NULL) return;

    stack s;
    initStack(&s);

    push(&s,root);
    while(!isEmpty(&s)){
        Node* cur=pop(&s);
        printf("%d-> ",cur->data);
        if(cur->right!=NULL)push(&s,cur->right);
        if(cur->left!=NULL)push(&s,cur->left);
    }
}

int main(){
    Node* root=createNode(1);
    root->left=createNode(2);
    root->right=createNode(3);
    root->left->left=createNode(4);
    root->left->right=createNode(5);
    root->right->right = createNode(6);

    printf("Preorder: ");
    preorder(root);

}