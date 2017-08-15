#include "../cpp/parse.cpp"
#include<iostream>
#include<bits/stdc++.h>

/*
    TEST FUNCTION

    1-> Contains invalid commands ie. r,/ , OUTPUT -> NULL
    2-> Contains a ] before any [ OUTPUT -> NULL
    3-> Contains unequal number of [ and ] OUTPUT -> NULL
    4-> Valid Command
    5-> Valid Command

*/


char str1[4] = {'r' , '/' , '.' , '<'};
char str2[5] = {'.' , ']' , '.' , '>' , '['};
char str3[5] = {'[' , '[' , '.' , '.' , ']'};
char str4[7] = {'<' , '[' , '.' , '[' , '-' , ']' , ']'};
char str5[16] = {'+' , '+' , '[' , '-' , '>' , '+' , '['
                , '-' , '+' , '-' , ']' , '<' , ']' , '-' , '-' , '>'};


bool test_case(char *code , int sz) {
    node **ptr = parse(code , sz);
    if ( ptr == NULL ) {
        return 0;
    }
    return 1;
}

void tests() {
    int pass = 0, fail = 0;

    if ( !test_case(str1 , 4) ) {
        printf("Case 1: OK \n");
        pass++;
    } else {
        printf("Case 1: FAIL \n");
        fail++;
    }
    if ( !test_case(str2 , 5) ) {
        printf("Case 2: OK \n");
        pass++;
    } else {
        printf("Case 2: FAIL \n");
        fail++;
    }

    if ( !test_case(str3 , 5) ) {
        printf("Case 3: OK \n");
        pass++;
    } else {
        printf("Case 3: FAIL \n");
        fail++;
    }

    if ( test_case(str4 , 7) ) {
        printf("Case 4: OK \n");
        pass++;
    } else {
        printf("Case 4: FAIL \n");
        fail++;
    }
    if ( test_case(str5 , 16) ) {
        printf("Case 5: OK \n");
        pass++;
    } else {
        printf("Case 5: FAIL \n");
        fail++;
    }

    if ( fail ) {
        printf("STATUS: INCORRECT \n");
    } else {
        printf("STATUS: CORRECT \n");
    }
}

int main() {
    tests();
}
