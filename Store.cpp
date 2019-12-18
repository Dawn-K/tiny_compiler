//
// Created by DawnK on 2019/12/18.
//

#include "Store.h"

string Store::judgeRegOrMem(string var) {
    string temp = Avalue[var].reg;
    if (!temp.empty() && Register.count(temp) && Register[temp].used && Register[temp].content == var) {
        return temp;
    }
    return Avalue[var].mem;
}

bool Store::isdigit(string var) {
    for (auto it: var) {
        if (it < '0' || it > '9') {
            return false;
        }
    }
    return true;
}

string Store::getType(string var) {
    if (isdigit(var)) {
        return var;
    } else {
        return judgeRegOrMem(var);
    }
}

// 将寄存器中的内容存入内存，空出寄存器
void Store::storeReg(string reg) {
    Register[reg].used = 0;
    MEM.append("1");
    string tmp("Mov DS:word ptr[" + to_string(MEM.top) + "]");
    Avalue[Register[reg].content] = "[" + to_string(MEM.top) + "]";
    assCode.push_back(tmp);
}

void Store::genMov(string var1, string var2) {
    string temp = getType(var2);
    string s = "";
    if (!Register.count(var1)) { // var1不是寄存器，而是内存
        // 此处还需严谨测试，感觉可能会出现死循环?
        // genMov->conToReg->applyReg->genMov
        // 难道在这里需要独断一下？强行赋值？
        // todo : 重大问题
        // todo 此处需要判断var2是不是常数，如果是，需要用寄存器过渡一下。如果temp是寄存器则直接转就可
        if (isdigit(temp)) { // 如果var2是常数，需要先把这个常数加入寄存器中
            temp = conToReg(var2);
        }
        s = "Mov DS:word ptr" + var1 + " " + temp;
    } else { // var1 是寄存器,无需判断temp，直接赋值即可
        s = "Mov " + var1 + " " + temp;
        Register[var1].content = var2;
        Register[var1].used = 1;
        Avalue[var2].reg = var1;
    }
    assCode.push_back(s);
}

// 通用的申请寄存器，var是变量或者常数都可。
string Store::applyReg(string var) {
    int far_index = -1; // 变量下次被使用的最远坐标
    string best = ""; // 最后选中的最合适的寄存器
    for (const auto &it:Register) {
        if (!it.second.used) { // 发现空闲寄存器
            return it.first;
        }
        string oldVar = it.second.content;
        if (Avalue[oldVar].vlist.empty()) {
            return it.first;
        } else if (Avalue[oldVar].vlist[0] > far_index) {
            far_index = Avalue[oldVar].vlist[0];
            best = it.first;
        }
    }
    storeReg(best);
    genMov(best, var);
    Register[best].used = 1;
    return best;
}

// 为某个变量申请寄存器，如果已经在寄存器中，则返回寄存器；如果不在，则申请一个
string Store::varToReg(string var) {
    string reg = Avalue[var].reg;
    // 已经在寄存器中
    if (Register.count(reg) && Register[reg].used && Register[reg].content == var) {
        return reg;
    }
    return applyReg(var);
}

// 为常数申请寄存器
string Store::conToReg(string con) {
    return applyReg(con);
}
