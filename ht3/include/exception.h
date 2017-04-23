#pragma once
#include <stdexcept>

class HuffmanException : public std::logic_error {
public:
    HuffmanException(std::string msg) : logic_error(msg) {;}
};

