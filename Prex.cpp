//
// Created by DawnK on 2019/12/19.
//

#include "Prex.h"

void Prex::append(Quat q) {
    ++top;
    v.push_back(q);
}

Quat Prex::pop() {
    --top;
    Quat tmp = v.back();
    v.pop_back();
    return tmp;
}

Quat Prex::getQuta(int id) {
    if (id >= v.size()) {
        cerr << " getQuta error" << endl;
    }
    return v[id];
}

string Prex::newTemp() {
    ++tDex;
    return "T" + to_string(tDex);
}

// 回填
void Prex::backFill(int old, int aim) {
    v[old].ans = to_string(aim);
}

void Prex::clear() {
    base = 0;
    top = -1;
    tDex = -1;
    v.clear();
}

void Prex::print() {
    cout << "print Prex" << endl;
    for (const auto &it: v) {
        if (it.op != "Call" && it.op != "Par") {
            cout << it.op << " " << it.n1 << " " << it.n2 << " " << it.ans << endl;
        } else {
            cout << it.op << " " << it.n1 << endl;
        }
    }
}
