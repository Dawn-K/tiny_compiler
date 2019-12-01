//
// Created by DawnK on 2019/12/1.
//

#ifndef COMPLIER_TEST_NUM_CHECKER_LL1_H
#define COMPLIER_TEST_NUM_CHECKER_LL1_H

#include "Lexical_Analysiser.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

struct Quat {
    string op, n1, n2, ans;
};

class Num_Checker_LL1 {
private:
    int Index;
    int len;
    Out buff;
    stack<char> SYN;
    stack<string> SEM;
    int tmp_index = 1;
    map<pair<string, string>, pair<string, char> > LL1map;
    vector<Out> token;
    map<string, int> delimiter, numtable;
    vector<Quat> q;
    map<string, int> pre;

    Out Next();

    bool check(Out o, string str);

    void ins(string a, string b, string str, char op);

    bool check();

    void reset();

    char buffTochar();

    string findnum(Out o);

    void addQuta();

public:
    Num_Checker_LL1();

    Num_Checker_LL1(Lexical_Analysiser &a);

    bool maincheck();

    bool CreatQuat();

    void showQuat();
};

#endif //COMPLIER_TEST_NUM_CHECKER_LL1_H
