#include "eval.hpp"
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<math.h>


/*
    Copyright 2017 Yogesh Aggarwal


    Evaluate Function
    vector v stores the values at each point.
*/


std::vector<int>v;

std::string stin = "" , stout = "" , stx = "";

int fact(int n) {
    return !n ? 1 : n*fact(n-1);
}

int pow(int base, int exp) {
    return !exp ? 1 : base*pow(base,exp-1);
}

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
        scanf("%c \n" , &l);
        stin += l;
        v[ptr] = l;
        return ptr;
    }
    if ( c == '[' ) {
        loop(cur->l , ptr, mxptr, cur_size);
        return ptr;
    }
}

void com_sp(node *cur , int ptr , int mxptr , int cur_size) {
    if ( cur->fc[0] == 's' && cur->fc[1] == 'r' ) {
        v[ptr] = v[ptr]*v[ptr];
    }
    if ( cur->fc[0] == 's' && cur->fc[1] == 'q' ) {
        v[ptr] = floor(sqrt(v[ptr]));
    }
    if ( cur->fc[0] == 'f' && cur->fc[1] == 'a' && cur->fc[2] == 'c' && cur->fc[3] == 't' ) {
        v[ptr] = fact(v[ptr]);
    }
    if ( cur->fc[0] == 'm' ) {
        mxptr = std::max(cur->a , mxptr); mxptr = std::max(cur->b , mxptr); mxptr = std::max(cur->cs , mxptr);
        gr_table(mxptr , cur_size);
        v[cur->cs] = v[cur->a]*v[cur->b];
    }
    if ( cur->fc[0] == 'd' ) {
        mxptr = std::max(cur->a , mxptr); mxptr = std::max(cur->b , mxptr); mxptr = std::max(cur->cs , mxptr);
        gr_table(mxptr , cur_size);
        v[cur->cs] = v[cur->a]/v[cur->b];
    }
    if ( cur->fc[0] == 'e' ) {
        mxptr = std::max(cur->a , mxptr); mxptr = std::max(cur->b , mxptr); mxptr = std::max(cur->cs , mxptr);
        gr_table(mxptr , cur_size);
        v[cur->cs] = pow(v[cur->a] , v[cur->b]);
    }
    if ( cur->fc[0] == 'm' && cur->fc[1] == 'v' ) {
        mxptr = std::max(cur->a , mxptr); mxptr = std::max(cur->b , mxptr);
        gr_table(mxptr , cur_size);
        v[cur->b] = v[cur->a];
        v[cur->a] = 0;
    }
}

void evaluate(node *cmd) {
    node *cur = cmd;
    int ptr = 0 , mxptr = 0 , cur_size = 0;
    v.clear();
    v.resize(10);
    stin = "" ; stout = ""; stx = "";
    while ( cur->r != NULL && cur->r != NULL ) {
        if ( cur->sp == 1 ) {
            com_sp(cur , ptr , mxptr , cur_size);
        } else {
            ptr = command(cur , cur->c , ptr , mxptr , cur_size);
        }
        cur = cur->r;
    }
    if ( cur->sp == 1 ) {
        com_sp(cur , ptr , mxptr , cur_size);
    } else {
        command(cur , cur->c , ptr , mxptr , cur_size);
    }
}
