//
// Created by DawnK on 2019/11/19.
//

#ifndef COMPLIER_TEST_LEXICAL_ANALYSISER_H
#define COMPLIER_TEST_LEXICAL_ANALYSISER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

struct Out {
    int ind;
    int type;

    Out(int _type, int _index) {
        type = _type, ind = _index;
    }

    Out() = default;
};

class Lexical_Analysiser {
private:
#define maxsize 100
    string buff;
    int id_index, ch_index, str_index, num_index;
    int status;
    int k_index = 1;
    int d_index = 1;
    string trans = " iCSckp";
    string keyword[maxsize];;
    map<string, int> identifier;
    map<char, int> chartable;
    map<string, int> stringtable;
//    string stringtable[maxsize];

    int ins_indentifier(const string &str);

    int ins_chartable(char ch);

    int ins_numtable(const string &str);

    int ins_stringtable(const string &str);

    int check_keyword(const string &s);

    int check_delimiter(const string &s);

public:
    vector<Out> token;
    map<string, int> delimiter, numtable;

    Lexical_Analysiser();

    bool work(char ch);

    void showtable();

    void showToken();

};

#endif //COMPLIER_TEST_LEXICAL_ANALYSISER_H
