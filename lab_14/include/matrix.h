#include <iostream>
#include <fstream>

#pragma once 

class MatrixException : public std::logic_error {
public:
    MatrixException(std::string msg) : logic_error(msg) {;}
};


class Matrix {
public:
    Matrix(int w = 0, int h = 0);
    Matrix(const Matrix& a);
    ~Matrix();
    
    Matrix& operator= (const Matrix& other);
    Matrix& operator+= (const Matrix& other);
    Matrix& operator*= (const Matrix& other);
    
    int get(int i, int g);
    
    int rows();
    int cols();    
  
    friend std::ifstream& operator>>(std::ifstream& is, Matrix& m);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
          
private:
    int rows_;
    int cols_;
    int** data_;
};
