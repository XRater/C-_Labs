#pragma once
#include "Test.h"
#include "huffman.h"


class HuffmanTest : public Test {
public:
    void test_get_symbols_freq();
    void test_get_leafes();
    void test_set_codes();
    
    void test_encode_text();
    void test_print_tech_info();

    void test_read_symbols_freq();
    
    void runAllTests();
};

