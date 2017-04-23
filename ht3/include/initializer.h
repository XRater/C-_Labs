#pragma once
#include <string>
#include "exception.h"

class Initializer {
    
    friend class InitTest;

public:
    Initializer(int argc, char** const argv);

    void run() const;    

private:        
    int mode_;
    std::string input_;
    std::string output_;
    
    Initializer(const Initializer& other);
    Initializer& operator=(const Initializer);
};

