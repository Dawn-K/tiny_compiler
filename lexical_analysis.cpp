//
// Created by DawnK on 2019/10/8.
//

#include "lexical_analysis.h"

Out::Out(int type, int value) : type(type), value(value) {}

Out::Out() {}

void LexicalAnalyzer::init_reserve_table() {
    reserve_table_size = 1;
    // printf("done!\n");
    FILE *reserve = fopen("reserve", "r");
    char *tmp_buff = (char *) malloc(100 * sizeof(char));
    while (fscanf(reserve, "%s", tmp_buff) != EOF) {
        //  printf("read : %s\n", tmp_buff);
        reserve_table[reserve_table_size] = (char *) malloc(sizeof(tmp_buff) + 1);
        strcpy(reserve_table[reserve_table_size], tmp_buff);
        ++reserve_table_size;
    }
    // printf("done2!\n");
    FILE *delimiter = fopen("delimiter", "r");
    while (fscanf(delimiter, "%s", tmp_buff) != EOF) {
        reserve_table[reserve_table_size] = (char *) malloc(sizeof(tmp_buff) + 1);
        strcpy(reserve_table[reserve_table_size], tmp_buff);
        index[std::string(reserve_table[reserve_table_size])] = reserve_table_size + 2;
        ++reserve_table_size;
    }
//    for (int i = 1; i < reserve_table_size; ++i) {
//        printf("No.%d %s\n", i, reserve_table[i]);
//    }
//    printf("done3!\n");
}

// 如果FindInReserve函数的返回值小于3,则表示没找到
Out LexicalAnalyzer::FindInReserve(char *word, bool &flag) {
    int word_position = 0;
    for (int i = 1; i < reserve_table_size; ++i) {
        if (strcmp(reserve_table[i], word) == 0) {
            word_position = i;
            break;
        }
    }
    flag = word_position != 0;
    //  printf("  word \"%s\" pos+2 == %d ", word, word_position + 2);
    return {word_position + 2, -1};
}

Out LexicalAnalyzer::FindInSymbol(char *word) {
    int word_position = 0;
    for (int i = 1; i < symbol_table_size; ++i) {
        if (strcmp(symbol_table[i], word) == 0) {
            word_position = i;
            break;
        }
    }
    if (word_position == 0) {
        char *new_word_ptr = (char *) malloc(strlen(word) + 1);
        strcpy(new_word_ptr, word);
        word_position = symbol_table_size;
        symbol_table[symbol_table_size++] = new_word_ptr;
    }

    return {1, word_position};
}

Out LexicalAnalyzer::FindInConstant(char *word) {
    int word_position = 0;
    for (int i = 1; i < constant_table_size; ++i) {
        if (strcmp(constant_table[i], word) == 0) {
            word_position = i;
            break;
        }
    }
    if (word_position == 0) {
        char *new_word_ptr = (char *) malloc(strlen(word) + 1);
        strcpy(new_word_ptr, word);
        word_position = constant_table_size;
        constant_table[constant_table_size++] = new_word_ptr;
    }
    return {2, word_position};
}

LexicalAnalyzer::LexicalAnalyzer(int symbolTableSize, int reserveTableSize, int constantTableSize) : symbol_table_size(
        symbolTableSize), reserve_table_size(reserveTableSize), constant_table_size(constantTableSize) {}

LexicalAnalyzer::LexicalAnalyzer() {
    index.clear();
    token_position = 0;
    buff_position = 0;
    status = 1;
    symbol_table_size = 1;
    reserve_table_size = 1;
    constant_table_size = 1;
    init_reserve_table();
}

int LexicalAnalyzer::Next(char ch) {
    if (ch == '\n') {
        return true;
    }
    //  printf("ch == %c sta == %d ", ch, status);
    bool accpeted;
    if (status == 1) { // 梦开始的地方
        if (ch != ' ') { // 如果处于开始状态时遇到空格,则跳过,其他情况时空格应当做截止符
            if (isalpha(ch)) {
                status = 2;
            } else if (isdigit(ch)) {
                status = 3;
            } else {
                status = 4;
            }
            buff[buff_position++] = ch;
        }
        accpeted = true;
    } else if (status == 2) { // 标识符/保留字
        if (isalnum(ch)) { //仅接受数字/字母
            buff[buff_position++] = ch;
            accpeted = true;
        } else {
            buff[buff_position] = '\0';
            //    printf("find var \'%s\'", buff);
            buff_position = 0;
            bool is_find_in_reserve = false;
            Out current_token = FindInReserve(buff, is_find_in_reserve);
            if (!is_find_in_reserve) {
                current_token = FindInSymbol(buff);
            }
            //   printf(" token %d : %d ", current_token.type, current_token.value);
            token[token_position++] = current_token;
            // printf("add var \'%s\'", symbol_table[token[token_position - 1].value]);
            status = 1;
            accpeted = false;
        }
    } else if (status == 3) {  // 常量
        if (isdigit(ch)) { // 仅接受数字
            buff[buff_position++] = ch;
            accpeted = true;
        } else {
            buff[buff_position] = '\0';
            buff_position = 0;
            token[token_position++] = FindInConstant(buff);
            //   printf("add const \'%s\'", constant_table[token[token_position - 1].value]);
            status = 1;
            accpeted = false;
        }
    } else { // 处理特殊符号
        if (!isalnum(ch) && ch != ' ') { //只要不是普通字符和空格,就接受
            buff[buff_position++] = ch;
            accpeted = true;
        } else {
            buff[buff_position] = '\0';
            buff_position = 0;
            token[token_position++] = Out(index[std::string(buff)], -1);
            //   printf("  find opr \'%s\'   ", buff);
            status = 1;
            accpeted = false;
        }
    }
    //  printf("-> %d  \n", status);
    return accpeted;
}


void LexicalAnalyzer::Show() {
    for (int i = 0; i < token_position; ++i) {
        printf("(%d %d)", token[i].type, token[i].value);
        if (token[i].type == 1) {
            printf("%s", symbol_table[token[i].value]);
        } else if (token[i].type == 2) {
            printf("%s", constant_table[token[i].value]);
        } else {
            printf("%s", reserve_table[token[i].type - 2]);
        }
        printf("\n");
    }
}

void LexicalAnalyzer::ShowSymbol() {
    printf(" == Symbol == \n");
    for (int i = 1; i < symbol_table_size; ++i) {
        printf("%s\n", symbol_table[i]);
    }
}

void LexicalAnalyzer::ShowConstant() {
    printf(" == Constant == \n");
    for (int i = 1; i < constant_table_size; ++i) {
        printf("%s\n", constant_table[i]);
    }
}
