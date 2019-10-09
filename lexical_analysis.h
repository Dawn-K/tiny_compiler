//
// Created by DawnK on 2019/10/8.
//

#ifndef TINY_COMPILER_LEXICAL_ANALYSIS_H
#define TINY_COMPILER_LEXICAL_ANALYSIS_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <string>

const int kSymbolTableMaxSize = 100;
const int kReserveTableMaxSize = 100;
const int kConstantTableMaxSize = 100;
const int kBuffMaxSize = 100;
const int kTokenMaxSize = 100;

struct Out {
    int type, value;

    Out();

    Out(int type, int value);
};

class LexicalAnalyzer {
private:
    char *symbol_table[kSymbolTableMaxSize];
    int symbol_table_size;
    char *reserve_table[kReserveTableMaxSize];
    int reserve_table_size;
    char *constant_table[kConstantTableMaxSize];
    int constant_table_size;
    int status;
    char buff[kBuffMaxSize];
    int buff_position;
    Out token[kTokenMaxSize];
    int token_position;
    std::unordered_map<std::string, int> index;

    // TODO: 常数是用字符还是用数字呢?暂且用字符
    void init_reserve_table();


    Out FindInReserve(char *word, bool &flag);

    Out FindInSymbol(char *word);

    Out FindInConstant(char *word);

public:
    LexicalAnalyzer();

    int Next(char ch);

    void Show();

    void ShowSymbol();

    void ShowConstant();

    LexicalAnalyzer(int symbolTableSize, int reserveTableSize, int constantTableSize);

};


#endif //TINY_COMPILER_LEXICAL_ANALYSIS_H
