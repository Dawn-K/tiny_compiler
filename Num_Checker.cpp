//
// Created by DawnK on 2019/11/20.
//

#include "Num_Checker.h"

Num_Checker::Num_Checker() {}

Num_Checker::Num_Checker(Lexical_Analysiser &a) {
    token = a.token;
    delimiter = a.delimiter;
    Index = 0;
    len = token.size();
}

Out Num_Checker::Next() {
    if (Index != len) {
        ++Index;
//        cout << "read : " << token[Index - 1].type << " " << token[Index - 1].ind << endl;
        return token[Index - 1];
    }
    cerr << "Illegal expression" << endl;
    return {-1, -1};
}

bool Num_Checker::Z() {
    buff = Next();
//    if (buff.type != -1 && E() && buff.type == end.type && buff.ind == end.ind) {
    if (buff.type != -1 && E() && check(buff, "#")) {
        cout << "Accepted" << endl;
        return 1;
    } else {
        cout << "Wrong Answer" << endl;
        return 0;
    }
}

// E->TC
bool Num_Checker::E() {
    return T() && C();
}

// T->FD
bool Num_Checker::T() {
    return F() && D();
}

// C-> +TC|-TC|空
bool Num_Checker::C() {
    if (check(buff, "+")) { // +
        buff = Next();
        return buff.type != -1 && T() && C();
    } else if (check(buff, "-")) { // -
        buff = Next();
        return buff.type != -1 && T() && C();
    }
    return true;
}

// D-> *FD|/FD|空
bool Num_Checker::D() {
    if (check(buff, "*")) { // *
        buff = Next();
        return buff.type != -1 && F() && D();
    } else if (check(buff, "/")) { // /
        buff = Next();
        return buff.type != -1 && F() && D();
    }
    return true;
}

// F -> digit | (E)
bool Num_Checker::F() {
    if (buff.type == 4) { // digit
        buff = Next();
        return buff.type != -1;
    } else if (check(buff, "(")) {// (
        buff = Next();
        return buff.type != -1 && E() && check(buff, ")") && (buff = Next()).type != -1; // )
    }
    return 0;
}

void Num_Checker::reset() {
    Index = 0;
}

bool Num_Checker::check(Out o, string str) {
    if (o.type != 6) return false;
    for (const auto &it : delimiter) {
        if (it.second == o.ind) {
            return it.first == str;
        }
    }
    return false;
}

