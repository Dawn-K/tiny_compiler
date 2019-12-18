//
// Created by DawnK on 2019/12/18.
//

#ifndef COMPLIER_TEST_AVA_H
#define COMPLIER_TEST_AVA_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Ava {
private:

public:
    string reg, mem;
    vector<int> vlist;

    Ava() {
        reg = "";
        mem = "";
        vlist.clear();
    }

    Ava(const string &_mem) {
        reg = "";
        mem = "[" + _mem + "]";
        vlist.clear();
    }
};

#endif //COMPLIER_TEST_AVA_H
