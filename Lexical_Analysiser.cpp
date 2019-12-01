//
// Created by DawnK on 2019/11/19.
//


#include "Lexical_Analysiser.h"

inline bool isnum(char ch) {
    return ch <= '9' && ch >= '0';
}

int Lexical_Analysiser::ins_indentifier(const string &str) {
    if (identifier.count(str) == 1) {
        return identifier[str];
    }
    ++id_index;
    identifier[str] = id_index;
    return id_index;
}

int Lexical_Analysiser::ins_chartable(char ch) {
    if (chartable.count(ch) == 1) {
        return chartable[ch];
    }
    ++ch_index;
    chartable[ch] = ch_index;
    return num_index;
}
//int Lexical_Analysiser::ins_chartable(char ch) {
//    for (int i = 1; i < ch_index; ++i) {
//        if (chartable[i] == ch) {
//            return i;
//        }
//    }
//    chartable[ch_index] = ch;
//    ++ch_index;
//    return ch_index - 1;
//}

int Lexical_Analysiser::ins_stringtable(const string &str) {
    if (stringtable.count(str) == 1) {
        return stringtable[str];
    }
    ++str_index;
    stringtable[str] = str_index;
    return str_index;
}

// int1
bool Lexical_Analysiser::work(char ch) {
//    cerr << "status: " << status << endl;
    if (status == 1) {
        buff.clear();
        if (isalpha(ch) || ch == '_') {
            buff += ch;
            status = 2;
        } else if (isnum(ch)) {
            buff += ch;
            status = 3;
        } else if (ch == '\'') {
            status = 4;
        } else if (ch == '"') {
            status = 6;
        } else if (ch != ' ' && ch != '\n') { // 界符
            status = 7;
            return 1;
        } else {
            return 0;
        }
        return 0;
    } else if (status == 2) {
        if (isalnum(ch) || ch == '_') {
            buff += ch;
            status = 2;
            return 0;
        } else {
            status = 1;
            // solve the buff
            Out ans = Out(5, check_keyword(buff));
            if (ans.ind == -1) {
                ans = Out(1, ins_indentifier(buff));
            }
            token.push_back(ans);
            return 1;
        }
    } else if (status == 3) {
        if (isnum(ch) || ch == '.') {
            buff += ch;
            status = 3;
            return false;
        } else {
            status = 1;
            // solve the buff
            // TODO: const automata
            token.emplace_back(4, ins_numtable(buff));
            return 1;
        }
    } else if (status == 4) {
        buff += ch;
        status = 5;
        return 0;
    } else if (status == 5) {
        if (ch == '\'') {
            // buff
            token.emplace_back(2, ins_chartable(buff[0]));
            status = 1;
            return 0;
        } else {
            cerr << "err5! " << endl;
            exit(1);
        }
    } else if (status == 6) {
        if (ch != '\"') {
            status = 6;
            buff += ch;
        } else {
            status = 1;
            // buff
            Out ans = Out(3, ins_stringtable(buff));
            token.push_back(ans);
        }
    } else if (status == 7) { // 界符
        if (ch != '>' && ch != '<' && ch != '=') {
            status = 1;
            buff += ch;
            token.emplace_back(6, check_delimiter(buff));
        } else {
            if (ch == '>') {
                status = 8;
                buff += ch;
            } else if (ch == '<') {
                status = 9;
                buff += ch;
            } else {
                status = 10;
                buff += ch;
            }
        }
        return 0;
    } else if (status == 8 || status == 9 || status == 10) {
        status = 1;
        if (ch == '=') {
            buff += ch;
            token.emplace_back(6, check_delimiter(buff));
            return 0;
        } else {
            token.emplace_back(6, check_delimiter(buff));
            return 1;
        }
    }

    return 0;
}

int Lexical_Analysiser::ins_numtable(const string &str) {
    if (numtable.count(str) == 1) {
        return numtable[str];
    }
    ++num_index;
    numtable[str] = num_index;
    return num_index;
}

int Lexical_Analysiser::check_keyword(const string &s) {
    for (int i = 1; i < k_index; ++i) {
        if (keyword[i] == s) {
            return i;
        }
    }
    return -1;
}

int Lexical_Analysiser::check_delimiter(const string &s) {
    if (delimiter.count(s) == 1) {
        return delimiter[s];
    }
    return -1;
}

void Lexical_Analysiser::showToken() {
    cout << "=====token=====" << endl;
    int len = token.size();
    cout << "len == " << len << endl;
    for (int i = 0; i < len; ++i) {
        cout << trans[token[i].type] << "," << token[i].ind << endl;
    }
}

Lexical_Analysiser::Lexical_Analysiser() {
/*init keyword & delimiter*/
    k_index = 1;
    ifstream kin("keyword.txt");
    if (!kin.is_open()) {
        cout << "fail to init keyword" << endl;
        exit(1);
    }
    while (kin.good()) {
        string ch;
        kin >> ch;
        keyword[k_index] = ch;
        ++k_index;
    }
    kin.close();

    d_index = 1;
    ifstream din("delimiter.txt");
    if (!din.is_open()) {
        cout << "fail to init delimiter" << endl;
        exit(1);
    }
    while (din.good()) {
        string ch;
        din >> ch;
        delimiter[ch] = d_index;
        ++d_index;
    }
    din.close();


    /*start to read file*/
    id_index = 0;
    str_index = 0;
    ch_index = 0;
    num_index = 0;
    status = 1;
    token.clear();
}

void Lexical_Analysiser::showtable() {
    cout << "=====string table=====" << endl;
    for (const auto &it:stringtable) {
        cout << it.second << " " << it.first << endl;
    }
    cout << "=====char table=====" << endl;
    for (auto it:chartable) {
        cout << it.second << " " << it.first << endl;
    }
    cout << "=====num table=====" << endl;
    for (const auto &it:numtable) {
        cout << it.second << " " << it.first << endl;
    }
    cout << "=====indentifier table=====" << endl;
    for (const auto &it:identifier) {
        cout << it.second << " " << it.first << endl;
    }
    cout << "=====delimiter table=====" << endl;
    for (const auto &it:delimiter) {
        cout << it.second << " " << it.first << endl;
    }
    cout << "=====keyword table=====" << endl;
    for (int i = 1; i < k_index; ++i) {
        cout << i << " " << keyword[i] << endl;
    }
}