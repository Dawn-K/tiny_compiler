//
// Created by DawnK on 2019/12/1.
//

#include "Num_Checker_LL1.h"

using namespace std;
#define mp make_pair


Num_Checker_LL1::Num_Checker_LL1(Lexical_Analysiser &a) {
    token = a.token;
    token = a.token;
    delimiter = a.delimiter;
    numtable = a.numtable;
    Index = 0;
    len = token.size();

    ins("E", "I", "CT", 'p');
    ins("E", "(", "CT", 'p');

    ins("C", "+", "CT", 'n');
    ins("C", "-", "CT", 'n');
    ins("C", ")", "", 'p');
    ins("C", "#", "", 'p');

    ins("T", "I", "DF", 'p');
    ins("T", "(", "DF", 'p');

    ins("D", "+", "", 'p');
    ins("D", "-", "", 'p');
    ins("D", "*", "DF", 'n');
    ins("D", "/", "DF", 'n');
    ins("D", ")", "", 'p');
    ins("D", "#", "", 'p');


    ins("F", "I", "", 'n');
    ins("F", "(", ")E", 'n');

    ins(")", ")", "", 'n');

    ins("#", "#", "", 'o');

}

bool Num_Checker_LL1::check(Out o, string str) {
    if (o.type != 6) return false;
    for (const auto &it : delimiter) {
        if (it.second == o.ind) {
            return it.first == str;
        }
    }
    return false;
}

Out Num_Checker_LL1::Next() {
    if (Index != len) {
        ++Index;
//        cout << "read : " << token[Index - 1].type << " " << token[Index - 1].ind << endl;
        return token[Index - 1];
    }
    cerr << "Illegal expression" << endl;
    return {-1, -1};
}

void Num_Checker_LL1::ins(string a, string b, string str, char op) {
    LL1map[mp(a, b)] = mp(str, op);
}

bool Num_Checker_LL1::maincheck() {
    if (check()) {
        cout << "AC" << endl;
        return 1;
    } else {
        cout << "WA" << endl;
        return 0;
    }
}

bool Num_Checker_LL1::check() {
    stack<char> sta;
    sta.push('#');
    sta.push('E');
    char curchar;
    buff = Next();
    while (!sta.empty()) {
        char top = sta.top();
        sta.pop();
        curchar = buffTochar();
        string tmp = "";
        if (LL1map.count(mp(tmp + top, tmp + curchar)) == 0) {
            cout << "Can's find " << tmp + top << " " << tmp + curchar << endl;
            return false;
        } else {
            pair<string, char> ans = LL1map[mp(tmp + top, tmp + curchar)];
            cout << "find " << tmp + top << " " << tmp + curchar;
            cout << " get " << ans.first << " " << ans.second << endl;
            if (ans.second == 'n') {
                buff = Next();
            } else if (ans.second == 'o') { // # and #
                return true;
            }
            int len = ans.first.size();
            for (int i = 0; i < len; ++i) {
                cout << "push stack " << ans.first[i] << endl;
                sta.push(ans.first[i]);
            }
        }
    }
    return false;
}

void Num_Checker_LL1::reset() {
    Index = 0;
    while (!SYN.empty()) {
        SYN.pop();
    }
    while (!SEM.empty()) {
        SEM.pop();
    }
    tmp_index = 1;
}


bool Num_Checker_LL1::CreatQuat() {
    reset();
    pre[">"] = 4;
    pre["<"] = 4;
    pre[">="] = 4;
    pre["<="] = 4;
    pre["="] = 4;
    pre["+"] = 5;
    pre["-"] = 5;
    pre["*"] = 6;
    pre["/"] = 6;
    buff = Next();
    SYN.push('#');
    while (!SYN.empty()) {
        char curchar = buffTochar();
        char topchar = SYN.top();
//        cerr << "top " << topchar << "  curchar " << curchar << endl;
        string tmp = "";
        if (curchar == 'I') {
            SEM.push(findnum(buff)); // todo
            buff = Next();
        } else if (curchar == '(') {
            SYN.push('(');
            buff = Next();
        } else if (curchar == ')') {
            if (topchar == '(') {
                SYN.pop();
                buff = Next();
            } else if (topchar == '#') {
                cerr << "# and )" << endl;
                return 0;
            } else {    // w1
                // Q
                addQuta();
            }
        } else if (curchar == '#') {
            if (topchar == '(') {
                cerr << "( and #" << endl;
                return 0;
            } else if (topchar == '#') {
                cout << "success" << endl;
                return 1;
            } else {  //w1
                // Q
                addQuta();
            }
        } else {  // w2
            if (topchar == '#') { // todo
                SYN.push(curchar);
                buff = Next();
            } else if (topchar == '(') {
                SYN.push(curchar);
                buff = Next();
            } else { // w1 -> w2
                if (pre[tmp + topchar] < pre[tmp + curchar]) {
                    SYN.push(curchar);
                    buff = Next();
                } else {
                    // Q
                    addQuta();
                }
            }
        }
    }
    return 0;
}

char Num_Checker_LL1::buffTochar() {
    char curchar;
    if (buff.type == 4) {
        curchar = 'I';
    } else if (buff.type == 6 && check(buff, "+")) {
        curchar = '+';
    } else if (buff.type == 6 && check(buff, "-")) {
        curchar = '-';
    } else if (buff.type == 6 && check(buff, "*")) {
        curchar = '*';
    } else if (buff.type == 6 && check(buff, "/")) {
        curchar = '/';
    } else if (buff.type == 6 && check(buff, "(")) {
        curchar = '(';
    } else if (buff.type == 6 && check(buff, ")")) {
        curchar = ')';
    } else if (buff.type == 6 && check(buff, "#")) {
        curchar = '#';
    }
    return curchar;
}

string Num_Checker_LL1::findnum(Out o) {
    for (auto it:numtable) {
        if (it.second == o.ind) {
            return it.first;
        }
    }
    return std::string();
}

void Num_Checker_LL1::addQuta() {
    string empty;
    string op = empty + SYN.top();
    SYN.pop();
    string n2 = SEM.top();
    SEM.pop();
    string n1 = SEM.top();
    SEM.pop();
    string tmpname = "t" + to_string(tmp_index);
    ++tmp_index;
//    cout << "add " << op << " " << n1 << " " << n2 << " " << tmpname << endl;
    q.push_back(Quat{op, n1, n2, tmpname});

    SEM.push(tmpname);
}

void Num_Checker_LL1::showQuat() {
    cout<<"=====Quat====="<<endl;
    for (const auto &it:q) {
        cout <<"( "<< it.op << ", " << it.n1 << ", " << it.n2 << ", " << it.ans << " )"<<endl;
    }
}
