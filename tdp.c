//
// Created by darim on 2/22/2023.
//

#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "tdp.h"

char nextIn;

// Parse Table Points to Production Number
int parseTable[8][8] = {
        //             0      1     ~     (      )      |       &      e
        /*E*/ { 1, 1, 1, 1,-1,-1,-1,-1},
        /*ET*/{ 3, 3, 3, 3, 3, 2, 3, 3},
        /*T*/ { 4, 4, 4, 4,-1,-1,-1,-1},
        /*TT*/{ 6, 6, 6, 6, 6, 6, 5, 6},
        /*F*/ { 9, 9, 7, 8,-1,-1,-1,-1},
        /*S*/ {10,10,-1,-1,-1,-1,-1,-1},
        /*ST*/{11,11,12,12,12,12,12,12},
        /*B*/ {13,14,12,12,12,12,12,12}
};

// If the next input is the same as the parameter, return true
bool isMatch(char c){
    if(nextIn == c){
        return true;
    } else {
        return false;
    }
}

// Lookahead for the next input
char LOOKAHEAD(char* str, int curr){
    if(curr < strlen(str)){
        return str[curr];
    }
    return '\0';
}

// Check if the input is a terminal
bool isTerminal(char c){
    switch(c) {
        case '0':
        case '1':
        case '~':
        case '(':
        case ')':
        case '|':
        case '&':
        case 'e':
            return true;
    }
    return false;
}

//stack returns syntactic category label and cases will return index of row
int syncatRef(char *c){
    if(strcmp(c, "E")){
        return 0;
    } else if(strcmp(c, "ET")){
        return 1;
    } else if(strcmp(c, "T")){
        return 2;
    } else if(strcmp(c, "TT")){
        return 3;
    } else if(strcmp(c, "F")){
        return 4;
    } else if(strcmp(c, "S")){
        return 5;
    } else if(strcmp(c, "ST")){
        return 6;
    } else if(strcmp(c, "B")){
        return 7;
    } else return -1;
}

//should the stack pop a terminal, use these cases to refer to a column in the table
int charRef(char c){
    switch(c){
        case '0':
            return 0;
        case '1':
            return 1;
        case '~':
            return 2;
        case '(':
            return 3;
        case ')':
            return 4;
        case '|':
            return 5;
        case '&':
            return 6;
        default:
            return 7;
    }
}

TREE parseFun(char* in) {
    // Initialize the Stack and push the start symbol
    STACK stack = createStack();
    push(stack, "E");
    TREE tree = makeNode0("E");

    while(!isEmpty(stack)) {
        // Get the next input
        nextIn = LOOKAHEAD(in, 0);

        // Get the top of the stack
        char* top = pop(stack);

        // If the top of the stack is a terminal
        if(isTerminal(top[0])) {
            // If the next input is the same as the top of the stack
            if(isMatch(top[0])) {
                // Remove the next input
                in++;
            } else {
                // Error
                printf("Parse Failed");
                return FAILED;
            }
        } else {
            // Get the row and column of the parse table
            int row = syncatRef(top);
            int col = charRef(nextIn);

            // Get the production number from the parse table
            int prodNum = parseTable[row][col];

            // If the production number is -1, error
            if(prodNum == -1) {
                printf("Parse Failed");
                return NULL;
            }
        }
    }
}



