//
// Created by DawnK on 2019/12/19.
//

#ifndef COMPLIER_TEST_PREX_H
#define COMPLIER_TEST_PREX_H

#include <iostream>
#include <vector>
#include <string>
#include "Quta.h"

using namespace std;

class Prex {
private:
public:
    int top, tDex, base;
    vector<Quat> v;

    void append(Quat q);

    Quat pop();

    Quat getQuta(int id);

    string newTemp();

    void backFill(int old, int aim);

    void clear();

    void print();
};

#endif //COMPLIER_TEST_PREX_H
