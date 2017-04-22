#pragma once
#include <string>
#include <stdexcept>

class HuffmanException : public std::logic_error {
public:
    HuffmanException(std::string msg) : logic_error(msg) {;}
};


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

