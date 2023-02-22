#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#ifndef PROJECT_2_PARSE_TREE_TREE_H
#define PROJECT_2_PARSE_TREE_TREE_H

#define FAILED NULL
#define INPUT_CHAR 255

typedef struct NODE *TREE;
struct NODE {
    char *label;
    TREE leftmostChild, rightSibling;
};

TREE makeNode0(char *x);
TREE makeNode1(char *x, TREE t);
TREE makeNode2(char *x, TREE t1, TREE t2);
TREE makeNode3(char *x, TREE t1, TREE t2, TREE t3); TREE E();

void printParseTree(TREE root, int level);
void freeTree(TREE root);

bool lookahead(char c);
bool match(char c);
TREE parse(char* input);



#endif //PROJECT_2_PARSE_TREE_TREE_H
