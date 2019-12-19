//
// Created by DawnK on 2019/12/18.
//

#ifndef COMPLIER_TEST_AVA_H
#define COMPLIER_TEST_AVA_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

class Ava {
private:

public:
    string reg, mem;
    queue<int> vlist;

    Ava() {
        reg = "";
        mem = "";
        while (!vlist.empty()) {
            vlist.pop();
        }
    }

    Ava(const string &_mem) {
        reg = "";
        mem = "[" + _mem + "]";
        while (!vlist.empty()) {
            vlist.pop();
        }
    }
};

#endif //COMPLIER_TEST_AVA_H
