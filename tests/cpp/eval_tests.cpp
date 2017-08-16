#include "../cpp/eval.cpp"
#include<string>

/*
    Copyright 2017 Yogesh Aggarwal

*/


// Test case 1 -> INVALID COMMAND


std::string test1 = "-.>,reg,][";


// Test case 2 -> Adds the values 2 and 5 and prints 7

std::string test2 = "++>+++++[<+>-]++++++++[<++++++>-]<.";


// Test case 3 -> Prints "Hello World"


std::string test3 = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";


// Test case 4 -> Accepts two characters and prints them


std::string test4 = ",>,<.>.";

void tests() {
    int pass = 0, fail = 0;

    node *t1 = parse(&test1[0] , test1.length());
    if ( t1 == NULL ) {
        printf("Case 1: OK \n");
        pass++;
    } else {
        printf("Case 1: FAIL \n");
        fail++;
    }
    node *t2 = parse(&test2[0] , test2.length());
    evaluate(t2);
    if ( stx == "7" ) {
        printf(" \nCase 2: OK \n");
        pass++;
    } else {
        printf("Case 2: FAIL \n");
        fail++;
    }

    node *t3 = parse(&test3[0] , test3.length());
    evaluate(t3);
    if ( stx == "Hello World!\n" ) {
        printf("Case 3: OK \n");
        pass++;
    } else {
        printf("Case 3: FAIL \n");
        fail++;
    }

    node *t4 = parse(&test4[0] , test4.length());
    evaluate(t4);
    if ( stin == stout ) {
        printf(" \nCase 4: OK \n");
        pass++;
    } else {
        printf("Case 4: FAIL \n");
        fail++;
    }

    if ( fail ) {
        printf("INCORRECT \n");
    } else {
        printf("CORRECT \n");
    }
}

int main() {
    tests();
}


