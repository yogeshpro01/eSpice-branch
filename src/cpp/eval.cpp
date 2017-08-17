#include "eval.hpp"
#include "parse.hpp"
#include "parse.cpp"

/*
    Copyright 2017 Yogesh Aggarwal


    Evaluate Function
    vector v stores the values at each point.
*/


std::vector<int>v;

std::string stin = "" , stout = "" , stx = "";


int command(node * , char , int, int, int);

void loop(node *st, int ptr, int mxptr, int cur_size) {
    while ( v[ptr] ) {
        node *x = st; int cur = ptr;
        while ( x->c != ']' ) {
            cur = command(x , x->c , cur, mxptr , cur_size);
            x = x->r;
        }
    }
}


/*
    We use the concept of table doubling for managing memory
*/


void gr_table(int mxptr , int cur_size) {
    if ( mxptr + 1 >= cur_size ) {
        v.resize(2*cur_size);
    } else if ( mxptr <= 1/4*cur_size ) {
        v.resize(cur_size/2);
    }
}

int command(node *cur, char c, int ptr, int mxptr, int cur_size) {
    mxptr = std::max(ptr , mxptr);
    gr_table(mxptr , cur_size);
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
        loop(cur->l , ptr, mxptr, cur_size);
        return ptr;
    }
}

void evaluate(node *cmd) {
    node *cur = cmd;
    int ptr = 0 , mxptr = 0 , cur_size = 0;
    v.clear();
    v.resize(10);
    stin = "" ; stout = ""; stx = "";
    while ( cur->r != NULL && cur->r != NULL ) {
        ptr = command(cur , cur->c , ptr, mxptr, cur_size);
        cur = cur->r;
    }
    command(cur , cur->c , ptr, mxptr , cur_size);
}
