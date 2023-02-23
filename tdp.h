//
// Created by darim on 2/22/2023.
//

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

#ifndef PROJECT_2_PARSE_TREE_TDP_H
#define PROJECT_2_PARSE_TREE_TDP_H

#endif //PROJECT_2_PARSE_TREE_TDP_H

typedef struct TDP* TDP;

struct TDP{
    int curr;
    STACK stack;
};

extern TDP newTDP(char* input);

char LOOKAHEAD(char* str, int curr);
bool isTerminal(char c);
//stack returns syntactic category label and cases will return index of row
int syncatRef(char *c);
int charRef(char c);