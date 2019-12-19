//
// Created by DawnK on 2019/12/18.
//

#include "Tack.h"

Tack::Tack() {
    top = -2;
    while (!stk.empty()) {
        stk.pop();
    }
}

void Tack::append(string var) {
    ++top;
    stk.push(var);
}

string Tack::pop() {
    --top;
    string res = stk.top();
    stk.pop();
    return res;
}

string Tack::getTop() {
    return stk.top();
}

