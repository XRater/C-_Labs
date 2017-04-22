#include <sstream>
#include <iostream>

#include "ReadPrintTest.h"

#define DO_CHECK(EXPR) Test::check(EXPR, __FUNCTION__, __FILE__, __LINE__); 


void ReadPrintTest::runAllTests() {
    test_printer_flush();
    test_printer_accum();
    test_printer_print();
}


void ReadPrintTest::test_printer_flush() {
    std::stringstream out;
    BinaryPrinter printer(&out);
    char* s = new char[20];
    
    printer.buff_ = "0000000011111111";
    printer.flush();
    DO_CHECK(printer.printed_chars_ == 2);
    out.read(s, 2);
    DO_CHECK(s[1] == -1 && s[0] == 0);
    printer.buff_.clear();

    printer.buff_ = "";
    printer.flush();
    DO_CHECK(printer.printed_chars_ == 2);
    printer.buff_.clear();

    printer.buff_ = "011111111";
    printer.flush();
    DO_CHECK(printer.printed_chars_ == 4);
    out.read(s, 2);
    DO_CHECK(s[0] == 127 && s[1] == -128);

    delete [] s;
}


void ReadPrintTest::test_printer_accum() {
    BinaryPrinter printer;
    printer.accum("001001");
    printer.accum("1101");
    printer.accum("");
    DO_CHECK(printer.buff_ == "0010011101");
}


void ReadPrintTest::test_printer_print() {
    std::stringstream out;
    char* s = new char[10];
    
    BinaryPrinter printer(&out);
    printer.buff_ = "111111110000110100000110001";
    printer.print_char_(0);
    printer.print_char_(8);
    printer.print_char_(9);    
    out.read(s, 3);   
    DO_CHECK(s[0] = -128 && s[1] == 13 && s[2] == 26);
    delete [] s;
}

