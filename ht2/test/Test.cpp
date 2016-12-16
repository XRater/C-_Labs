#include "Test.h"
#include <iostream>

int Test::failedNum = 0;
int Test::totalNum = 0;



void Test::check(bool expr, const char *func, const char  *filename, int lineNum) {
    Test::totalNum++;
    if (!expr) {
        Test::failedNum++;
        std::cout << "test faied: " << func << " in " << filename << ":" << lineNum << '\n';
    }
}


void Test::showFinalResult() {
    std::cout << "Tests number: " << totalNum << "; Tests failed: " << failedNum << "\n"; 
    if (!failedNum)
        std::cout << "OK\n";
}        

