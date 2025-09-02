#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

char opStack[MAX];
int opTop = -1;

void pushOp(char c) {
    if (opTop < MAX - 1) opStack[++opTop] = c;
}
char popOp() {
    if (opTop >= 0) return opStack[opTop--];
    return '\0';
}
char peekOp() {
    if (opTop >= 0) return opStack[opTop];
    return '\0';
}

int precedence(char op) {
    if (op == '/' || op == '*') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char* exp, char* output) {
    int i = 0, k = 0;
    while (exp[i] != '\0') {
        char c = exp[i];

        if (isdigit(c)) {
            output[k++] = c;
        }
        else if (c == '(') {
            pushOp(c);
        }
        else if (c == ')') {
            while (opTop >= 0 && peekOp() != '(') {
                output[k++] = popOp();
            }
            popOp(); // remove '('
        }
        else { // operator
            while (opTop >= 0 && precedence(peekOp()) >= precedence(c)) {
                output[k++] = popOp();
            }
            pushOp(c);
        }
        i++;
    }
    while (opTop >= 0) {
        output[k++] = popOp();
    }
    output[k] = '\0';
}

int valStack[MAX];
int valTop = -1;

void pushInt(int x) {
    if (valTop < MAX - 1) valStack[++valTop] = x;
}
int popInt() {
    if (valTop >= 0) return valStack[valTop--];
    return 0;
}

int evalPostfix(char* exp) {
    int i = 0;
    while (exp[i] != '\0') {
        char c = exp[i];

        if (isdigit(c)) {
            pushInt(c - '0'); // char → int
        }
        else {
            int b = popInt();
            int a = popInt();
            switch (c) {
                case '+': pushInt(a + b); break;
                case '-': pushInt(a - b); break;
                case '*': pushInt(a * b); break;
                case '/': pushInt(a / b); break;
            }
        }
        i++;
    }
    return popInt();
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    printf("Value: %d\n", evalPostfix(postfix));
    return 0;
}
