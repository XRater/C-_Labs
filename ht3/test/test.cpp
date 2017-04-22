#include "HuffmanTest.h"
#include "InitTest.h"
#include "ReadPrintTest.h"

int main() {
    InitTest it;
    it.runAllTests();

    HuffmanTest ht;
    ht.runAllTests();

    ReadPrintTest rt;
    rt.runAllTests();

    Test::showFinalResult();
    return 0;
}


