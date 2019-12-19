//
// Created by DawnK on 2019/12/18.
//

#ifndef COMPLIER_TEST_STORE_H
#define COMPLIER_TEST_STORE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include "Reg.h"
#include "Ava.h"
#include "Tack.h"
#include "Quta.h"

using namespace std;

class Store {
private:
    map<string, Reg> Register;
    map<string, Ava> Avalue;
    Tack MEM; // 未分配的内存
    vector<string> assCode;

    bool isdigit(string var);

    void resetReg();

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

    void genAddSub(Quat q, string func);

    void genMulDix(Quat q, string func);

    string findEmptyReg(string var);

    string applyReg(string var);

    string varToReg(string var);

    string conToReg(string con);

    void showReg();

    void showCode();

    void showAva();

    void Test();

    void refreshAva(int id);
};

#endif //COMPLIER_TEST_STORE_H
