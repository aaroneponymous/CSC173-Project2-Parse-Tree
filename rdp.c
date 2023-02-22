#include "rpd.h"
#include "tree.h"

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