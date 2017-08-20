#ifndef PARSE_INCLUDE
#define PARSE_INCLUDE

/* The parse function accepts a string containing Brain****++ code
 * It must split the code into tokens as defined by the language specification
 * Look at the document for an example
 * */

#include <stddef.h>

struct node {
    char c;
    int sp;
    char fc[4];
    int a,b,cs;
    node *l , *r;
    node() {
        l = NULL; r = NULL;
    }
 };

bool validate(char *code, int sz);
node *parse(char *code, int sz);
node *parse_sp(node *x, char *code);
bool val_sp(char *code, int sz, int cur);
int skp(char code);
bool cm(char c);

#endif
