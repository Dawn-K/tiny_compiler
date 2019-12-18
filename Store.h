//
// Created by DawnK on 2019/12/18.
//

#ifndef COMPLIER_TEST_STORE_H
#define COMPLIER_TEST_STORE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Reg.h"
#include "Ava.h"
#include "Tack.h"

using namespace std;

class Store {
private:
    map<string, Reg> Register;
    map<string, Ava> Avalue;
    Tack MEM; // 未分配的内存
    vector<string> assCode;

    bool isdigit(string var);

public:
    Store() {
        Register.insert(make_pair("AX", Reg()));
        Register.insert(make_pair("BX", Reg()));
        Register.insert(make_pair("CX", Reg()));
        Register.insert(make_pair("DX", Reg()));
        Avalue.clear();
        assCode.clear();
    }

    string judgeRegOrMem(string var);

    string getType(string var);

    void storeReg(string reg);

    void genMov(string var1, string var2);

    string applyReg(string var);

    string varToReg(string var);

    string conToReg(string con);
};

#endif //COMPLIER_TEST_STORE_H
