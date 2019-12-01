//
// Created by DawnK on 2019/11/20.
//

#ifndef COMPLIER_TEST_NUM_CHECKER_H
#define COMPLIER_TEST_NUM_CHECKER_H

#include "Lexical_Analysiser.h"

class Num_Checker {
private:
    bool E();

    bool T();

    bool C();

    bool D();

    bool F();

    Out Next();

    int Index;
    int len;
    Out buff;
    vector<Out> token;
//    Out end = Out(6, 19); // #
    map<string, int> delimiter;
    bool check(Out o,string str);
public:
    bool Z();

    void reset();

    Num_Checker();

    Num_Checker(Lexical_Analysiser &a);
};

#endif //COMPLIER_TEST_NUM_CHECKER_H
