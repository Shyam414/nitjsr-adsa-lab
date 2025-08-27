#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

// Stack for operators
char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1) stack[++top] = c;
}

char pop() {
    if (top >= 0) return stack[top--];
    return '\0';
}

char peek() {
    if (top >= 0) return stack[top];
    return '\0';
}

// precedence of operators
int precedence(char op) {
    if (op == '/' || op == '*') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char* exp, char* output) {
    int i = 0, k = 0;
    while (exp[i] != '\0') {
        char c = exp[i];
        
        if (isdigit(c)) { // operand → directly to output
            output[k++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top >= 0 && peek() != '(') {
                output[k++] = pop();
            }
            pop(); // remove '('
        }
        else { // operator
            while (top >= 0 && precedence(peek()) >= precedence(c)) {
                output[k++] = pop();
            }
            push(c);
        }
        i++;
    }

    while (top >= 0) {
        output[k++] = pop();
    }
    output[k] = '\0';
}

int main() {
    char expr[MAX], output[MAX];
    printf("Enter infix expression: ");
    scanf("%s", expr);

    infixToPostfix(expr, output);
    printf("Postfix: %s\n", output);

    return 0;
}
