//
// Created by DawnK on 2019/12/18.
//

#ifndef COMPLIER_TEST_REG_H
#define COMPLIER_TEST_REG_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Reg {
private:
public:
    bool used;
    string content;

    Reg() {
        used = 0;
        content = "";
    }

};


#endif //COMPLIER_TEST_REG_H
