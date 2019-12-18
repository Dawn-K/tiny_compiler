//
// Created by DawnK on 2019/12/18.
//

#ifndef COMPLIER_TEST_TACK_H
#define COMPLIER_TEST_TACK_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using namespace std;

// todo : 还需进一步完善此栈
class Tack {
private:
    stack<string> stk;
public:
    int top;

    Tack();

    void append(string var);

    string pop();

    string getTop();


};

#endif //COMPLIER_TEST_TACK_H
