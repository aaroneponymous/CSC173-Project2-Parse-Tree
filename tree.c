#include "tree.h"

// Make Nodes and Subtrees
TREE makeNode0(char *x)
{
    TREE root;
    root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}
TREE makeNode1(char *x, TREE t)
{
    TREE root;
    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}
TREE makeNode2(char *x, TREE t1, TREE t2)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    return root;
}
TREE makeNode3(char *x, TREE t1, TREE t2, TREE t3)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    return root;
}

// Print Tree
// Recursively Print the Parse Tree
// Track Levels and Indent
void printParseTree(TREE root, int level) {
    if (!root) return;
    for (int i = 0; i < level; i++) {
        printf(" ");
    }
    printf("%s\n", root->label);
    printParseTree(root->leftmostChild, level+2);
    printParseTree(root->rightSibling, level);
}

// Free Tree
void freeTree(TREE root)
{
    if (root == NULL) return;
    freeTree(root->leftmostChild);
    freeTree(root->rightSibling);
    free(root);
}

char *nextTerminal; /* current position in input string */


bool lookahead(char c) {
    return *nextTerminal == c;
}

bool match(char c) {
    if (lookahead(c)) {
        nextTerminal += 1;
        return true;
    } else {
        return false;
    }
}

TREE parse(char* input) {
    nextTerminal = input;
    TREE parseTree = E();
    if (parseTree != NULL && lookahead('\0')) {
        return parseTree;
    } else {
        return FAILED;
    }
}
