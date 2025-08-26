#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;

void pushInt(int x) {
    if (top < MAX - 1) stack[++top] = x;
}

int popInt() {
    if (top >= 0) return stack[top--];
    return 0;
}

int evalPostfix(char* exp) {
    int i = 0;
    while (exp[i] != '\0') {
        char c = exp[i];
        
        if (isdigit(c)) {
            pushInt(c - '0'); // convert char to int
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <infix_expression>\n", argv[0]);
        return 1;
    }

    char postfix[MAX];
    extern void infixToPostfix(char* exp, char* output); // use function from part 1
    

    infixToPostfix(argv[1], postfix);
    printf("Postfix: %s\n", postfix);
    printf("Value: %d\n", evalPostfix(postfix));

    return 0;
}
