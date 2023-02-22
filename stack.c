#include "stack.h"


// Create Stack
STACK createStack() {
    STACK stack = (STACK) malloc(sizeof(struct STACKNODE));
    stack->top = NULL;
    return stack;
}

void push(STACK stack, char *x) {
    LL new = (LL) malloc(sizeof(struct LLNODE));
    new->label = x;
    new->next = stack->top;
    stack->top = new;
}
char *pop(STACK stack) {
    if (isEmpty(stack)) return NULL;
    char *x = stack->top->label;
    stack->top = stack->top->next;
    return x;
}
char *peek(STACK stack) {
    if (isEmpty(stack)) return NULL;
    return stack->top->label;
}
bool isEmpty(STACK stack) {
    return stack->top == NULL;
}
void freeStack(STACK stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}