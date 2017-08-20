#include "parse.hpp"
#include<iostream>
#include<stdlib.h>
#include<stack>
#include<map>


// Copyright 2017 Yogesh Aggarwal


node *q , *t , *tx , *pt;


// nodes to traverse through the linked list


std::stack<node*>t_head;


// contains all the pointers to the [ in the string


std::map<char , int>mp , mp2;


// map to all the commands in brain****, stores 1 if valid command else 0


char str[13] = {'.' , ',' , '+' , '-' , '<' , '>' , '[' , ']'};
char strsp[5] = {'s' , 'f' , 'm' , 'd' , 'e'};


// all the valid commands in brain****


/*
    validate(char *code)

    Function to check if the given code is a correct brain**** code or not

    1. Checks if all the characters are valid or not
    2. Checks that for each opening bracket, there is a closing bracket
    3. Checks that there is no closing bracket before an opening one

    Returns true if valid or else false
*/


bool cm(char c) {
    if ( c - '0' >= 0 && c - '0' <= 9 ) return 1;
    return 0;
}

int skp(char code) {
    if ( code == 's' ) {
        return 1;
    }
    return 3;
}

bool val_sp(char *code, int sz, int cur) {
    if ( *code == 's' ) {
        if ( cur + 1 < sz ) {
            if ( *(code+1) == 'r' || *(code+1) == 'q' ){
                return 1;
            }
        }
    } else if ( *code == 'f' ) {
        if ( cur + 3 < sz ) {
            if ( *(code+1) == 'a' && *(code+2) == 'c' && *(code+3) == 't' ) {
                return 1;
            }
        }
    } else if ( *code == 'm' || *code == 'd' || *code == 'e' ) {
        if ( cur + 3 < sz ) {
            if ( *(code+1) == 'v' ) {
                if ( cm(*(code+2)) && cm(*(code+3)) ) {
                    return 1;
                }
            } else {
                if ( cm(*(code+1)) && cm(*(code+2)) && cm(*(code+3)) ) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


bool validate(char *code, int sz) {
    for ( int i = 0; i < 8; i++ ) {
        mp[str[i]] = 1;
    }
    for ( int i = 0; i < 5; i++ ) {
        mp2[strsp[i]] = 1;
    }
    int ct = 0, x = 0;
    while ( *code != '\0' && x < sz ) {
        if ( !mp[*code] && ! mp2[*code]) {
            return 0;
        }
        if ( mp2[*code] ) {
            if ( !val_sp(code , sz, x) ) return 0;
            code += skp(*code);
        }
        if ( *code == ']' && !ct ) {
            return 0;
        }
        if ( *code == '[' ) ct++;
        if ( *code == ']' ) ct--;
        code++; x++;
    }
    return ct == 0 ? 1 : 0;
}


/*

    Program to parse the give code into arrays
    As for every [ ] we need a separate array, we create a dynamic list.
    Each node stores the command, and two pointers, l and r.

    If we have to nest an array we point the element next to [ on l and store the position (of [) in the stack
    whenever we get ], pop the top element from the stack and set its r to the next element of ]
    else we point the element to r


    so for example ++[->+[-+-]<]-->

                                                    ['-'] -> ['+'] -> ['-'] -> [']']
                                                     ^
                                                     |
                        ['-'] -> ['>'] -> ['+'] -> ['['] -> ['<'] -> [']']
                        ^
                        |
    ['+'] -> ['+'] -> ['['] -> ['-'] -> ['-'] -> ['>']
*/


node *parse_sp(node *x, char *code) {
    if ( *code == 's' && *(code+1) == 'q' ) {
        x->a = x->b = x->cs = 0;
        x->fc[0] = *code; x->fc[1] = *(code+1);
    }
    if ( *code == 's' && *(code+1) == 'r' ) {
        x->a = x->b = x->cs = 0;
        x->fc[0] = *code; x->fc[1] = *(code+1);
    }
    if ( *code == 'f' && *(code+1) == 'a' && *(code+2) == 'c' && *(code+3) == 't' ) {
        x->a = x->b = x->cs = 0;
        x->fc[0] = *code; x->fc[1] = *(code+1); x->fc[2] = *(code+2); x->fc[3] = *(code+3);
    }
    if ( *code == 'm' ) {
        x->a = *(code+1)-'0'; x->b = *(code+2)-'0'; x->cs = *(code+3)-'0';
        x->fc[0] = *code;
    }
    if ( *code == 'd' ) {
        x->a = *(code+1)-'0'; x->b = *(code+2)-'0'; x->cs = *(code+3)-'0';
        x->fc[0] = *code;
    }
    if ( *code == 'e' ) {
        x->a = *(code+1)-'0'; x->b = *(code+2)-'0'; x->cs = *(code+3)-'0';
        x->fc[0] = *code;
    }
    if ( *code == 'm' && *(code+1) == 'v' ) {
        x->a = *(code+2)-'0'; x->b = *(code+3)-'0';
        x->fc[0] = *code; x->fc[1] = *(code+1);
    }
    return x;
}

node *parse(char *code, int sz) {
    char *c2 = code;
    if ( !validate(c2 , sz) ) {
        return NULL;
    }
    q = new node; pt = new node;
    int fl = 0, st = 0, x = 0;
    while ( *code != '\0' && x < sz ) {
        t = new node;
        t->c = *code; t->l = NULL; t->r = NULL;
        if ( mp2[*code] ) {
            t->sp = 1;
            t = parse_sp(t , code);
            code += skp(*code);
        }
        if ( !st ) {
            pt = q = t; st++;
        } else {
            if ( fl == 1 ) {
                t_head.top()->l = t;
            } else if ( fl == 2 ) {
                t_head.top()->r = t;
                t_head.pop();
            } else {
                q->r = t;
            }
            q = t;
        }
        if ( *code == '[' ) {
            t_head.push(t);
            fl = 1;
        } else if ( *code == ']' ) {
            fl = 2;
        } else {
            fl = 0;
        }
        code++; x++;
    }
    return pt;
}

