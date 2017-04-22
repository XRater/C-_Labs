#pragma once
#include "Test.h"
#include "archiver.h"


class ReadPrintTest : public Test {
public:
    void runAllTests();
    
    void test_printer_flush();
    void test_printer_accum();
    void test_printer_print();
};

