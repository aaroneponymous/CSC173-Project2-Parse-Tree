#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define FAILED NULL
#define INPUT_CHAR 255

typedef struct NODE *TREE;
struct NODE {
    char *label;
    TREE leftmostChild, rightSibling;
};
//free tree
void freeTree(TREE root) {
    if (root == NULL) return;
    freeTree(root->leftmostChild);
    freeTree(root->rightSibling);
    free(root);
}

// Linked List Data Structure

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

TREE makeNode0(char *x);
TREE makeNode1(char *x, TREE t);
TREE makeNode2(char *x, TREE t1, TREE t2);
TREE makeNode3(char *x, TREE t1, TREE t2, TREE t3);
TREE makeNode4(char *x, TREE t1, TREE t2, TREE t3, TREE t4); TREE E();

// TREE FUNCTIONS
TREE E(); TREE ET(); TREE T(); TREE TT(); TREE F(); TREE S(); TREE ST(); TREE B();

TREE parseTree; /* holds the result of the parse */
char *nextTerminal; /* current position in input string */

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


// Part 1: Recursive Descent Parser
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
TREE makeNode4(char *x, TREE t1, TREE t2, TREE t3, TREE t4)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    return root;
}

// Syntactical Category <B> 0 or 1
TREE B()
{
    // If Symbol 0 (Use Production 13)
    if (lookahead('0')) {
        // Match and Return Node with 0
        if(!match('0')) return FAILED;
        return makeNode1("B", makeNode0("0"));

        // If Symbol 1 (Use Production 14)
    } else if (lookahead('1')) {
        // Match and Return Node with 1
        if(!match('1')) return FAILED;
        return makeNode1("B", makeNode0("1"));
    } else return FAILED;
}
// Syntactical Category <ST> S or Epsilon
TREE ST()
{
    // Use Production 12 for Epsilon
    if (!lookahead('0') && !lookahead('1')) {
        return makeNode1("ST", makeNode0("e"));
    } else {
        // Use Production 11 for S
        // Parse S
        TREE s = S();
        if (s == NULL) return FAILED;

        return makeNode1("ST", s);

    }

}
// Syntactical Category <S> B ST
TREE S()
{
    // Use Production 10 for B ST
    // Parse B
    TREE b = B();
    if (b == NULL) return FAILED;
    // Parse ST
    TREE st = ST();
    if (st == NULL) return FAILED;
    return makeNode2("S", b, st);
}
// Syntactical Category <F> ~ F or ( E ) or S
TREE F()
{
    // Use Production 7 for ~ F
    if (lookahead('~')) {
        // Match ~
        if(!match('~')) return FAILED;
        // Parse F
        TREE f = F();
        if (f == FAILED) return FAILED;
        return makeNode2("F", makeNode0("~"), f);

        // Use Production 8 for ( E )
    } else if (lookahead('(')) {
        // Match (
        if(!match('(')) return FAILED;
        // Parse E
        TREE e = E();
        if (e == NULL) return FAILED;
        // Match )
        if(!match(')')) return FAILED;
        return makeNode3("F", makeNode0("("), e, makeNode0(")"));

        // Use Production 9 for S
    } else {

        // Parse S
        TREE s = S();
        if (s == NULL) return FAILED;
        return makeNode1("F", s);
    }
}
// Syntactical Category <TT> & T or Epsilon
TREE TT()
{
    // Use Production 6 for Epsilon
    if (!lookahead('&')) {
        return makeNode1("TT", makeNode0("e"));
    } else {
        // Use Production 5 for & T
        // Match &
        if(!match('&')) return FAILED;
        // Parse T
        TREE t = T();
        if (t == FAILED) return FAILED;

        return makeNode2("TT", makeNode0("&"), t);
    }
}
// Syntactical Category <T> F TT
TREE T()
{
    // Parse F
    TREE f = F();
    if (f == FAILED) return FAILED;
    // Parse TT
    TREE tt = TT();
    if (tt == FAILED) return FAILED;

    return makeNode2("T", f, tt);
}
// Syntactical Category <ET> | E or Epsilon
TREE ET()
{
    // Use Production 3 for Epsilon
    if (!lookahead('|')) {
        return makeNode1("ET", makeNode0("e"));
    } else {
        // Use Production 2 for | E
        // Match |
        if(!match('|')) return FAILED;
        // Parse E
        TREE e = E();
        if (e == NULL) return FAILED;
        return makeNode2("ET", makeNode0("|"), e);
    }
}
// Syntactical Category <E> T ET
TREE E()
{
    // Parse T
    TREE t = T();
    if (t == FAILED) return FAILED;
    // Parse ET
    TREE et = ET();
    if (et == FAILED) return FAILED;
    return makeNode2("E", t, et);
}


// Part 2: Table Driven Parser

// Table Driven Parser Table
// First Row is the Non-Terminal Symbols
// First Column is the Terminal Symbols
// Each Cell is the Production to Use
// If the Cell is 0, then the Production is not valid

/* List of Productions
   1. E -> T ET
   2. ET -> | E
   3. ET -> ϵ
   4. T -> F TT
   5. TT -> & T
   6. TT -> ϵ
   7. F -> ~ F
   8. F -> ( E )
   9. F -> S
   10. S -> B ST
   11. ST -> S
   12. ST -> ϵ
   13. B -> 0
   14. B -> 1
*/

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
    return stack->top->next == NULL;
}
void freeStack(STACK stack) {
    while (!isEmpty(stack)) {
        pop(stack);
        stack->top->next = NULL;
    }

    free(stack->top);
    free(stack);
}


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
            parseTree = parse(inputString);

            // Check if the parse was successful
            if (parseTree == FAILED) {
                printf("Parse Failed\n");
            } else {
                printf("Parse Successful: \n\n");
                printParseTree(parseTree, 0);
            }
        }

    }


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



}
