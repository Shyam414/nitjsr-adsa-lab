#include <stdio.h>
#define SIZE 5

typedef struct {
    int items[SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *q) { q->front = q->rear = -1; }
int isEmpty(Queue *q) { return q->front == -1; }
int isFull(Queue *q) { return q->rear == SIZE - 1; }

void enqueue(Queue *q, int val) {
    if (isFull(q)) return;
    if (isEmpty(q)) q->front = 0;
    q->items[++q->rear] = val;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front++];
    if (q->front > q->rear) q->front = q->rear = -1; // reset
    return val;
}

typedef struct {
    Queue q1, q2;
} Stack;

void push(Stack *s, int val) {
    enqueue(&s->q2, val);
    while (!isEmpty(&s->q1))
        enqueue(&s->q2, dequeue(&s->q1));

    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

int pop(Stack *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack empty\n");
        return -1;
    }
    return dequeue(&s->q1);
}

int main() {
    Stack s;
    initQueue(&s.q1);
    initQueue(&s.q2);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Popped: %d\n", pop(&s));
    push(&s, 40);
    printf("Popped: %d\n", pop(&s));

    return 0;
}
