#include "tree.h"

#ifndef PROJECT_2_PARSE_TREE_STACK_H
#define PROJECT_2_PARSE_TREE_STACK_H


// Create a LinkedList Node

typedef struct LLNODE *LL;
struct LLNODE {
    char *label;
    LL next;
};

// Define Stack
typedef struct STACKNODE *STACK;
struct STACKNODE {
    struct LLNODE *top;
};

// STACK FUNCTIONS
void push(STACK stack, char *x);
char *pop(STACK stack);
char *peek(STACK stack);
bool isEmpty(STACK stack);
STACK createStack();
void freeStack(STACK stack);
extern STACK createStack();


#endif //PROJECT_2_PARSE_TREE_STACK_H
