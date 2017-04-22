#include "InitTest.h"
#include <iostream>

#define DO_CHECK(EXPR) Test::check(EXPR, __FUNCTION__, __FILE__, __LINE__); 


void InitTest::runAllTests() {
    testCorrect();         
    testIncorrect();          
}


void InitTest::testCorrect() {
    try {
        std::vector <std::string> v = {"main", "-c", "-f", "in", "-o", "out"};
        fill_args(v);
        Initializer in1(argc, argv);
        clear();
        v.clear();
        DO_CHECK(in1.mode_ == 0 && in1.input_ == "in" && in1.output_ == "out");
        

        v = {"", "-u",  "-o", "-c", "-file", "-file"};
        fill_args(v);
        Initializer in2(argc, argv);
        clear();
        v.clear();
        DO_CHECK(in2.mode_ == 1 && in2.input_ == "-file" && in2.output_ == "-c");

        v = {"naaame", "-o", "output", "-u", "-f", "--"};
        fill_args(v);
        Initializer in3(argc, argv);
        clear();
        v.clear();
        DO_CHECK(in3.mode_ == 1 && in3.input_ == "--" && in3.output_ == "output");
        
        v = {"name", "-file", "-u", "-o", "-o", "-c"};
        fill_args(v);
        Initializer in4(argc, argv);
        clear();
        v.clear();
        DO_CHECK(in4.mode_ == 0 && in4.input_ == "-u" && in4.output_ == "-o");
    }
    catch (HuffmanException) {
        clear();
        DO_CHECK(1 == 0);
    }
}


void InitTest::testIncorrect() {
    std::vector <std::string> v;

    v = {"main", "-c", "-f", "file", "-o"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "-f", "file", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "-f", "-o", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "file", "-o", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-f", "file", "-o", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"-c", "-f", "file", "-o", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-g", "-f", "file", "-o", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "-files", "file", "-o", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "-f", "file", "-out", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "-f", "file", "-o", "out", "-o"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "-f", "file", "-o", "out", "-f"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "-c", "-f", "file", "-o", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "-f", "-o", "file", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-c", "-f", "file", "-u", "-o", "out"};
    DO_CHECK(1 == check_args(v));

    v = {"main", "-u", "-f", "file", "-o", "-u", "-u"};
    DO_CHECK(1 == check_args(v));
}

