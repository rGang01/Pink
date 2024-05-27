#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define the stack for characters
typedef struct {
    char items[100];
    int top;
} CharStack;

// Define the stack for integers
typedef struct {
    int items[100];
    int top;
} IntStack;

// Function to initialize the character stack
void initCharStack(CharStack* s) {
    s->top = -1;
}

// Function to check if the character stack is empty
int isCharStackEmpty(CharStack* s) {
    return s->top == -1;
}

// Function to push an item onto the character stack
void pushChar(CharStack* s, char item) {
    s->items[++(s->top)] = item;
}

// Function to pop an item from the character stack
char popChar(CharStack* s) {
    if (!isCharStackEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

// Function to get the top item from the character stack
char peekChar(CharStack* s) {
    if (!isCharStackEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

// Function to initialize the integer stack
void initIntStack(IntStack* s) {
    s->top = -1;
}

// Function to check if the integer stack is empty
int isIntStackEmpty(IntStack* s) {
    return s->top == -1;
}

// Function to push an item onto the integer stack
void pushInt(IntStack* s, int item) {
    s->items[++(s->top)] = item;
}

// Function to pop an item from the integer stack
int popInt(IntStack* s) {
    if (!isIntStackEmpty(s)) {
        return s->items[(s->top)--];
    }
    return 0;
}

// Function to check if the character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Function to get the precedence of the operator
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Function to reverse a string
void reverse(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Function to convert infix expression to prefix expression
void infixToPrefix(char* infix, char* prefix) {
    CharStack s;
    initCharStack(&s);
    reverse(infix);
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                prefix[k++] = infix[i++];
            }
            prefix[k++] = ' ';  // Add space to separate numbers
            i--;  // To reprocess the non-digit character
        } else if (infix[i] == ')') {
            pushChar(&s, infix[i]);
        } else if (infix[i] == '(') {
            while (!isCharStackEmpty(&s) && peekChar(&s) != ')') {
                prefix[k++] = popChar(&s);
                prefix[k++] = ' ';
            }
            popChar(&s);  // Remove ')'
        } else if (isOperator(infix[i])) {
            while (!isCharStackEmpty(&s) && precedence(peekChar(&s)) >= precedence(infix[i])) {
                prefix[k++] = popChar(&s);
                prefix[k++] = ' ';
            }
            pushChar(&s, infix[i]);
        }
    }
    while (!isCharStackEmpty(&s)) {
        prefix[k++] = popChar(&s);
        prefix[k++] = ' ';
    }
    prefix[k - 1] = '\0';  // Remove the trailing space and add null terminator
    reverse(prefix);
}

// Function to evaluate prefix expression
int evaluatePrefix(char* prefix) {
    IntStack s;
    initIntStack(&s);
    reverse(prefix);

    char* token = strtok(prefix, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            pushInt(&s, atoi(token));
        } else if (isOperator(token[0])) {
            int val1 = popInt(&s);
            int val2 = popInt(&s);
            switch (token[0]) {
                case '+':
                    pushInt(&s, val1 + val2);
                    break;
                case '-':
                    pushInt(&s, val1 - val2);
                    break;
                case '*':
                    pushInt(&s, val1 * val2);
                    break;
                case '/':
                    pushInt(&s, val1 / val2);
                    break;
            }
        }
        token = strtok(NULL, " ");
    }
    return popInt(&s);
}

int main() {
    char infix[100];
    char prefix[100];

    // Get the infix expression from the user
    printf("Enter infix expression: ");
    scanf("%[^\n]%*c", infix);

    // Convert infix to prefix
    infixToPrefix(infix, prefix);

    // Output the prefix expression
    printf("Prefix expression: %s\n", prefix);

    // Evaluate the prefix expression
    int result = evaluatePrefix(prefix);

    // Output the result
    printf("Result: %d\n", result);

    return 0;
}
