#include "parse.hpp"
#include<iostream>
#include<stdlib.h>
#include<stack>
#include<map>


node *q , *t , *tx , *pt;


// nodes to traverse through the linked list


std::stack<node*>t_head;


// contains all the pointers to the [ in the string


std::map<char , int>mp;


// map to all the commands in brain****, stores 1 if valid command else 0


char str[8] = {'.' , ',' , '+' , '-' , '<' , '>' , '[' , ']'};


// all the valid commands in brain****

/*
    validate(char *code)

    Function to check if the given code is a correct brain**** code or not

    1. Checks if all the characters are valid or not
    2. Checks that for each opening bracket, there is a closing bracket
    3. Checks that there is no closing bracket before an opening one

    Returns true if valid or else false
*/


bool validate(char *code) {
    for ( int i = 0; i < 8; i++ ) {
        mp[str[i]] = 1;
    }
    int ct = 0;
    while ( *code != '\0' ) {
        if ( !mp[*code] ) {
            return 0;
        }
        if ( *code == ']' && !ct ) {
            return 0;
        }
        if ( *code == '[' ) ct++;
        if ( *code == ']' ) ct--;
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


node **parse(char *code) {
    if ( !validate(code) ) {
        return NULL;
    }
    q = new node; pt = new node;
    int fl = 0, st = 0;
    while ( *code != '\0' ) {
        t = new node;
        t->c = *code; t->l = NULL; t->r = NULL;
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
    }
    return &pt;
}

