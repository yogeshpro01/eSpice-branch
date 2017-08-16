#include "eval.hpp"


/*
    Copyright 2017 Yogesh Aggarwal


    Evaluate Function
    vector v stores the values at each point.
*/


std::vector<int>v;

std::string stin = "" , stout = "" , stx = "";

int cur_size = 10 , mxptr = 0;

int command(node * , char , int);

void loop(node *st, int ptr) {
    while ( v[ptr] ) {
        node *x = st; int cur = ptr;
        while ( x->c != ']' ) {
            cur = command(x , x->c , cur);
            x = x->r;
        }
    }
}


/*
    We use the concept of table doubling for managing memory
*/


void gr_table(int mxptr) {
    if ( mxptr + 1 >= cur_size ) {
        v.resize(2*cur_size);
    } else if ( mxptr <= 1/4*cur_size ) {
        v.resize(cur_size/2);
    }
}

int command(node *cur, char c, int ptr) {
    mxptr = std::max(ptr , mxptr);
    gr_table(mxptr);
    if ( c == '+' ) {
        v[ptr]++;
        return ptr;
    }
    if ( c == '-' ) {
        v[ptr]--;
        return ptr;
    }
    if ( c == '>' ) {
        return ++ptr;
    }
    if ( c == '<' ) {
        return --ptr;
    }
    if ( c == '.' ) {
        printf("%c" , v[ptr]);
        stout += v[ptr]; stx += v[ptr];
        return ptr;
    }
    if ( c == ',' ) {
        char l;
        scanf("%c" , &l);
        stin += l;
        v[ptr] = l;
        return ptr;
    }
    if ( c == '[' ) {
        loop(cur->l , ptr);
        return ptr;
    }
}

void evaluate(node *cmd) {
    node *cur = cmd;
    int ptr = 0; mxptr = 0; cur_size = 0;
    v.clear();
    v.resize(10);
    stin = "" ; stout = ""; stx = "";
    while ( cur->r != NULL && cur->r != NULL ) {
        ptr = command(cur , cur->c , ptr);
        cur = cur->r;
    }
    command(cur , cur->c , ptr);
}
