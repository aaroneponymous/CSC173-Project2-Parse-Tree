#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "rpd.h"
#include "tdp.h"

int main()
{
    // Part 1: Parse the Input String and either return Failed or the Parse Tree

    printf("PART 1: RECURSIVE DESCENT PARSER\n");

    while (true) {
        char inputString[INPUT_CHAR];
        printf("\nEnter a string to parse (or \"quit\" to quit): ");
        fgets(inputString, sizeof(inputString), stdin);
        inputString[strcspn(inputString, "\n")] = '\0';

        // Check if user wants to quit
        if (strcmp(inputString, "quit") == 0) {
            break;
        } else {
            // Parse the input string
            TREE parseTree = parse(inputString);

            // Check if the parse was successful
            if (parseTree == FAILED) {
                printf("Parse Failed\n");
            } else {
                printf("Parse Successful: \n\n");
                printParseTree(parseTree, 0);
            }
        }

    }
/*

    // Test the Stack Implementation
    // Create a Stack
    // Push 1, 2, 3, 4, 5
    // Pop 5, 4, 3, 2, 1
    // Print the Stack
    // Test Case

    // Create a Stack
    STACK stack = createStack();
    // Push 1, 2, 3, 4, 5
    push(stack, (char *) '1');
    push(stack, (char *) '2');
    push(stack, (char *) '3');
    push(stack, (char *) '4');
    push(stack, (char *) '5');

    // Is the Stack Empty?
    if (isEmpty(stack)) {
        printf("Stack is Empty\n");
    } else {
        printf("Stack is not Empty\n");
    }

    // Pop 5, 4, 3, 2, 1
    printf("Popping: %c \n", pop(stack));
    printf("Popping: %c \n", pop(stack));
    printf("Popping: %c \n", pop(stack));
    printf("Popping: %c \n", pop(stack));
    printf("Popping: %c \n", pop(stack));

    // Is the Stack Empty?
    if (isEmpty(stack)) {
        printf("Stack is Empty\n");
    } else {
        printf("Stack is not Empty\n");
    }

    free(stack);
*/



}
