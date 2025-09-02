#include <stdio.h>
#define MAX 100

int stack1[MAX], stack2[MAX];
int top1 = -1, top2 = -1;

// Stack operations
void push1(int x) { stack1[++top1] = x; }
int pop1() { return stack1[top1--]; }
void push2(int x) { stack2[++top2] = x; }
int pop2() { return stack2[top2--]; }
int isEmpty1() { return top1 == -1; }
int isEmpty2() { return top2 == -1; }

// Method 1: Push costly
void enqueue(int x) {
    while (!isEmpty1()) {
        push2(pop1());
    }
    push1(x);
    while (!isEmpty2()) {
        push1(pop2());
    }
}

int dequeue() {
    if (isEmpty1()) {
        printf("Queue Underflow!\n");
        return -1;
    }
    return pop1();
}

int peek() {
    if (isEmpty1()) {
        printf("Queue Empty!\n");
        return -1;
    }
    return stack1[top1];
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    printf("Dequeued: %d\n", dequeue());
    enqueue(40);
    printf("Dequeued: %d\n", dequeue()); 
    printf("Peek: %d\n", peek());        
    return 0;
}
