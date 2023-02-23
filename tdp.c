//
// Created by darim on 2/22/2023.
//

#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "tdp.h"

char nextIn;

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

bool isMatch(char c){
    if(nextIn == c){
        return true;
    } else {
        return false;
    }
}

char
LOOKAHEAD(char* str, int curr){
    if(curr < strlen(str)){
        return str[curr];
    }
    return '\0';
}

//will take
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

TDP parseFun(char* in) {
    nextIn = 0;

}