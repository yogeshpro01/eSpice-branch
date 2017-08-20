#ifndef EVAL_INCLUDE
#define EVAL_INCLUDE

#include "parse.hpp"
#include "parse.cpp"

#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<math.h>

int command(node * , char , int, int, int);
void loop(node *st, int ptr, int mxptr, int cur_size);
void gr_table(int mxptr , int cur_size);
int command(node *cur, char c, int ptr, int mxptr, int cur_size);
void evaluate(node *cmd);
int pow(int base, int exp);
int fact(int n);
void com_sp(node *cur , int ptr , int mxptr , int cur_size);

#endif
