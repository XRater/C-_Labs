#include "matrix.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <string>

Matrix::Matrix(int r, int c) : rows_(r), cols_(c) {
    data_ = new int*[rows_];
    for (int i = 0; i < rows_; i++)
        data_[i] = new int[cols_];
}


Matrix::Matrix(const Matrix& other) {
    data_ = new int*[other.rows_];
    rows_ = other.rows_;
    cols_ = other.cols_;
    for (int i = 0; i < other.rows_; i++)
        data_[i] = new int[other.cols_];
    
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
            data_[i][j] = other.data_[i][j];
}


Matrix::~Matrix() {
    for (int i = 0; i < rows_; i++)
        delete [] data_[i];
    delete [] data_;
}


Matrix& Matrix::operator= (const Matrix& other) {
    Matrix tmp(other);
    
    std::swap(rows_, tmp.rows_);   
    std::swap(cols_, tmp.cols_);
    std::swap(data_, tmp.data_); 
    
    return *this;
}


Matrix& Matrix::operator+= (const Matrix& other) {
    if (cols_ != other.cols_ || rows_ != other.rows_)
        throw MatrixException("#ADD: dimensions do not match.\n");
    
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
            data_[i][j] += other.data_[i][j];
    
    return *this;
}


Matrix& Matrix::operator*= (const Matrix& other) {
    if (cols_ != other.rows_)
        throw MatrixException("#arg1.columns != #arg2.rows.\n");
  
    Matrix tmp(rows_, other.cols_);
    for(int i = 0; i < rows_; i++)
        for(int j = 0; j < other.cols_; j++) {
            tmp.data_[i][j] = 0;
            for(int k = 0; k < cols_; k++)
                tmp.data_[i][j] += data_[i][k] * other.data_[k][j];
        }
        
    *this = tmp;
    return *this;
}

int Matrix::get(int i, int j) {
    if (i <= 1 || i > rows_ || j <= 1 || j > cols_)
        throw MatrixException("ACCESS: bad index.\n");
  
    return data_[i][j];
}


std::ifstream& operator>>(std::ifstream& is, Matrix& m) {
    int w, h;
    is >> w >> h;
    
    Matrix tmp(w, h);
    for (int i = 0; i < tmp.rows_; i++)
        for (int j = 0; j < tmp.cols_; j++)
            is >> tmp.data_[i][j];    
    
    m = tmp;
    return is;
}


std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.rows_; i++) {
        for (int j = 0; j < m.cols_; j++)
            os << m.data_[i][j] << ' ';
        os << '\n';
    }
       
    return os;
}

