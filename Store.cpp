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
    // todo : MEM此处存疑，不知道如何处理,暂时的处理方案是保存到之前申请的地址,不再开辟新的内存.
//    MEM.append("1");
//    MEM.append("1");
    string oldADR = Avalue[Register[reg].content].mem;
    cout << "store " << reg << "  content " << Register[reg].content << endl;
    string tmp("MOV 1DS:word ptr" + oldADR + "," + reg);
//    Avalue[Register[reg].content].mem = "[" + to_string(MEM.top) + "]";
    assCode.push_back(tmp);
}

// 生成MOV 指令，此函数不会保存var1里面的数据，只会直接覆盖
// var1要么是内存，要么是寄存器
void Store::genMov(string var1, string var2) {
    string temp = getType(var2);
    string s = "";
    if (!Register.count(var1)) { // var1不是寄存器，而是内存
        if (isdigit(temp)) { // 如果var2是常数，需要先把这个常数加入寄存器中
            temp = conToReg(var2);
        }
        s = "MOV DS:word ptr[" + var1 + "]," + temp;
    } else { // var1 是寄存器,无需判断temp，直接赋值即可
        s = "MOV " + var1 + "," + temp;
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
    string em = findEmptyReg(var);
    if (!em.empty()) {
        return em;
    }
    for (const auto &it:Register) {
        string oldVar = it.second.content;
        if (Avalue[oldVar].vlist.front() > far_index) {
            far_index = Avalue[oldVar].vlist.front();
            best = it.first;
        }
    }
    storeReg(best);
    genMov(best, var);
    Register[best].used = 1;
    return best;
}

// 为某个变量申请寄存器，如果已经在寄存器中，则返回寄存器；如果不在，则申请一个(此处只是申请下来，并没有真正存入)
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

void Store::showReg() {
    for (const auto &it:Register) {
        cout << it.first << " " << it.second.used << " " << it.second.content << endl;
    }
}

void Store::Test() {
    // 基本通过测试
    Avalue.insert(make_pair("a", Ava("0")));
    Avalue.insert(make_pair("b", Ava("2")));
    Avalue.insert(make_pair("c", Ava("4")));
    Avalue.insert(make_pair("d", Ava("6")));
    Avalue.insert(make_pair("e", Ava("8")));
    Avalue.insert(make_pair("f", Ava("10")));
    Avalue.insert(make_pair("g", Ava("12")));
    Avalue["a"].vlist.push(10);
    Avalue["b"].vlist.push(10);
    Avalue["c"].vlist.push(10);
    Avalue["d"].vlist.push(10);
    Avalue["e"].vlist.push(9);
    Avalue["f"].vlist.push(10);
    Avalue["g"].vlist.push(8);
    varToReg("a");
    varToReg("b");
    varToReg("c");
    varToReg("d");
    //   showReg();
    varToReg("e");
    varToReg("f");
    varToReg("g");
    showReg();
//    showCode();
//    Quat q1 = Quat{"+", "a", "b", "g"};
//    genAddSub(q1, "ADD");
    Quat q2 = Quat{"*", "e", "b", "g"};
    genMulDix(q2, "MUL");
    showReg();
    showCode();
    showAva();
}


// 加法涉及多寄存器的分配问题，
void Store::genAddSub(Quat q, string func) {
    string type1 = getType(q.n1);
    string type2 = getType(q.n2);
    if (Register.count(type1)) { // n1在寄存器中
        cout << "n1 in  reg" << endl;
        // todo: 加法的寄存器分配还存在优化的余地
        // 这里还要考虑寄存器中原来变量的活跃性
        storeReg(type1); // 先保存n1,空出寄存器,然后将值暴力写入
        assCode.push_back(func + " " + type1 + "," + getType(q.n2));
        Avalue[q.ans].reg = type1;
        Register[type1].used = 1;
        Register[type1].content = q.ans;
    } else if (func == "ADD" && Register.count(type2)) {
        cout << "n2 in  reg" << endl;
        storeReg(type2); // 先保存n2,空出寄存器,然后将值暴力写入
        assCode.push_back(func + " " + type2 + "," + getType(q.n1));
        Avalue[q.ans].reg = type2;
        Register[type2].used = 1;
        Register[type2].content = q.ans;
    } else { // 都不在寄存器中
        cout << "both not reg" << endl;
        // 先给n1分配一个寄存器,然后用结果覆盖它(实际上优化不彻底)
        string reg = varToReg(q.n1);
        assCode.push_back(func + " " + reg + "," + getType(q.n2));
        Avalue[q.ans].reg = reg;
        Register[reg].used = 1;
        Register[reg].content = q.ans;
    }
}

// 乘除是单目运算,只能用AX
// todo: 后续再做深度优化,先运行起来再说
void Store::genMulDix(Quat q, string func) {
    string type1 = getType(q.n1);
    string type2 = getType(q.n2);
    if (type1 == "AX") {
        cout << "n1 in  AX" << endl;
        if (!Avalue[q.n1].vlist.empty()) {
            storeReg("AX");
        }
        string reg = "AX";
        assCode.push_back(func + " " + reg + "," + getType(q.n2));
        Avalue[q.ans].reg = reg;
        Register[reg].used = 1;
        Register[reg].content = q.ans;
    } else if (func == "MUL" && type2 == "AX") {
        cout << "n2 in  AX" << endl;
        if (!Avalue[q.n2].vlist.empty()) {
            storeReg("AX");
        }
        string reg = "AX";
        assCode.push_back(func + " " + reg + "," + getType(q.n1));
        Avalue[q.ans].reg = reg;
        Register[reg].used = 1;
        Register[reg].content = q.ans;
    } else { // 都不在寄存器中
        cout << "both not  in  AX" << endl;
        string reg = "AX";
        if (!isdigit(Register["AX"].content) && !Avalue[Register["AX"].content].vlist.empty()) {
            storeReg("AX");
        }
        genMov("AX", q.n1);
        assCode.push_back(func + " " + reg + " " + getType(q.n2));
        Avalue[q.ans].reg = reg;
        Register[reg].used = 1;
        Register[reg].content = q.ans;
    }
}
// 每生成一条目标代码，需要更新一次待用活跃信息链 √
void Store::refreshAva(int id) {
    for (auto it : Avalue) {
        if (!it.second.vlist.empty() && it.second.vlist.front() <= id) {
            it.second.vlist.pop();
        }
    }
}

string Store::findEmptyReg(string var) {
    //   cout << "try to  find empty reg" << endl;
    for (const auto &it:Register) {
        if (!it.second.used) { // 发现空闲寄存器
            genMov(it.first, var);  // 直接挤占寄存器,因为it.first一定是寄存器，所以直接覆盖不会造成死循环的问题
            return it.first;
        }
    }
    //   cout << "find const reg" << endl;
    for (const auto &it:Register) {
        if (isdigit(it.second.content)) { // 有的寄存器里面是常数
            genMov(it.first, var);  // 直接挤占寄存器
            return it.first;
        }
    }
    //  cout << "find unused reg" << endl;
    for (const auto &it:Register) {
        string oldVar = it.second.content;
        if (Avalue[oldVar].vlist.empty()) {
            // todo : 摸石头过河,如果后续不再用到旧变量，则直接覆盖
            genMov(it.first, var);  // 直接挤占寄存器
            return it.first;
        }
    }
    //   cout << "not find reg" << endl;
    return "";
}

void Store::resetReg() {
    for (auto it : Register) {
        it.second.reset();
    }
}


void Store::showCode() {
    for (const auto &it: assCode) {
        cout << it << endl;
    }
}

void Store::showAva() {
    for (const auto &it: Avalue) {
        cout << it.first << " " << it.second.mem << " " << it.second.reg << endl;
    }
}
