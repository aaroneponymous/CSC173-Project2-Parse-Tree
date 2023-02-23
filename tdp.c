//
// Created by darim on 2/22/2023.
//

#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "tdp.h"

char curr;
TDP newTDP(){
    TDP tdp = (TDP)malloc(sizeof(struct TDP));
    tdp->curr = 0;
    tdp->stack = createStack();
    tdp->strIn = NULL;
}

int parseTable[8][8] = {
        //             0      1     ~     (      )      |       &      e
        /*E*/ { 1, 1, 1, 1,-1,-1,-1,-1},
        /*ET*/{ 3, 3, 3, 3, 3, 2, 3, 3},
        /*T*/ { 4, 4, 4, 4,-1,-1,-1,-1},
        /*TT*/{ 6, 6, 6, 6, 6, 6, 5, 6},
        /*F*/ { 9, 9, 7, 8,-1,-1,-1,-1},
        /*S*/ {10,10,-1,-1,-1,-1,-1,-1},
        /*ST*/{11,11,12,12,12,12,12,12},
        /*B*/ {13,14,-1,-1,-1,-1,-1,-1}
};

bool isMatch(char c){
    if(curr == c){
        return true;
    } else {
        return false;
    }
}

char LOOKAHEAD(char* str, int curr){
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

//RETURNS LABEL OF SYNCAT USING INDEX FROM TABLE [i][j]
char* index_to_syncat(int n){
    if(n == 0){
        return "E";
    } else if(n == 1){
        return "ET";
    } else if(n == 2){
        return "T";
    } else if(n == 3){
        return "TT";
    } else if(n == 4){
        return "F";
    } else if(n == 5){
        return "S";
    } else if(n == 6){
        return "ST";
    } else if(n == 7){
        return "B";
    } else return NULL;
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

//int total = sizeof(*parseTable);
//const int numCols = sizeof((parseTable)[0]);
//const int numRows = total/numCols;

int col = 0;
int row = 0;
//STACK tStack = createStack();

void parseFun() {
    char* in = "(0)";
    int index = 0;
    curr = in[index];
    TDP tdp = newTDP();
    while(LOOKAHEAD != '\0'){
        col = charRef(curr);
        //find rows in that column and find ref to production
        int prodxnRef = parseTable[row][col];
        if(prodxnRef != -1){
            char* label = index_to_syncat(prodxnRef);
            tdp->stack.push(tdp->stack, label);
        }
    }
}