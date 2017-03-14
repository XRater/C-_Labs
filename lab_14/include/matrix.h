#include <iostream>
#include <fstream>

#pragma once 

class MatrixExeption {
public:
    virtual void inform() = 0;
};


class MatrixSumExeption : public MatrixExeption {
public:
    void inform();    
};


class MatrixMulExeption : public MatrixExeption {
public:
    void inform();    
};


class MatrixIndexExeption : public MatrixExeption {
public:
    void inform();    
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
