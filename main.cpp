#include<bits/stdc++.h>
#include "Lexical_Analysiser.h"
#include "Num_Checker.h"
#include "Num_Checker_LL1.h"

using namespace std;

// 标志符1 字符2 字符串3 常数4  关键字5 界符6
//  i C S c k p
int main() {
    Lexical_Analysiser la;
    FILE *fp = fopen("input.andy", "r");
    char ch;
    while (!feof(fp)) {
        ch = char(fgetc(fp));
        if (ch == EOF) {
            ch = ' ';
        }
        while (la.work(ch));
    }
    la.showToken();
//    Num_Checker nc(la);
//    nc.Z();
    Num_Checker_LL1 ncl(la);
//    ncl.maincheck();
    ncl.CreatQuat();
    ncl.showQuat();
    return 0;
}