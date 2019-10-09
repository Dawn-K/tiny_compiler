/*
No.1 program
No.2 procedure
No.3 begin
No.4 end
No.5 while
No.6 do
No.7 -
No.8 /
No.9 +
No.10 *
No.11 ;
No.12 :
No.13 :=
No.14 <
No.15 <=
No.16 #
 * */
#include "lexical_analysis.h"

int main(int argc, char *argv[]) {
    // argv[0]是可执行文件的名字,真正的参数从1开始,但是在开发过程中暂时还是别写了
//    for (int i = 1; i < argc; ++i) {
//        printf("arg: %s\n", argv[i]);
//    }
    LexicalAnalyzer la;
    FILE *fp;
    fp = fopen("sample.andy", "r");
    while (!feof(fp)) {
        char ch = char(fgetc(fp));
        while (!la.Next(ch));
    }
    la.Show();
    la.ShowSymbol();
    la.ShowConstant();
    return 0;
}
