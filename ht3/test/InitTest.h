#pragma once
#include "Test.h"
#include "initializer.h"

#include <vector>
#include <cstring>
#include <iostream>

class InitTest : public Test {
public:
    InitTest() {argv = new char*[10];}
    ~InitTest() {delete [] argv;}

    void testCorrect();
    void testIncorrect();

    void runAllTests();

private:
    void fill_args(std::vector <std::string>& v) {
        argc = v.size();

        for (size_t i = 0; i < argc; i++) {
            argv[i] = new char[v[i].length() + 1];
            for (size_t j = 0; j <= v[i].length(); j++)
                argv[i][j] = v[i][j]; 
        }
    }

    void clear() {
        for (size_t i = 0; i < argc; i++)
            delete[] argv[i];
    }
    
    bool check_args(std::vector <std::string>& v) {
        bool flag = 0;
        try {
            fill_args(v);
            Initializer in1(argc, argv);
            clear();
            v.clear();        
        }
        catch (HuffmanException) {
            clear();
            v.clear();
            flag = 1;            
        }
        return flag;
    }        
    
    
    size_t argc;
    char** argv;
};

