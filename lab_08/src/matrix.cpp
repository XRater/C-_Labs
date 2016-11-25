#include "matrix.h"
#include <iostream>

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int*[r];
    for (int i = 0; i < (int) r; i++)
        _data[i] = new int[c];
    for (int i = 0; i < (int) r; i++)
        for (int j = 0; j < (int) c; j++)
            _data[i][j] = 0;
}

Matrix::Matrix(const Matrix& m) {
    _rows = m._rows;
    _cols = m._cols;
    _data = new int*[_rows];
    for (int i = 0; i < (int) _rows; i++){
        _data[i] = new int[_cols];
        for (int j = 0; j < int(_cols); j++)
            _data[i][j] = m._data[i][j];
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < (int) _rows; i++)
        delete [] _data[i];
    delete [] _data;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) const{
    for (int i = 0; i < (int) _rows; i++){
        for (int j = 0; j < (int) _cols; j++)
            fprintf(f, "%d ", _data[i][j]);
        fprintf(f, "\n");    
    }
}

bool Matrix::operator==(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols)
        return false;
    for (int i = 0; i < (int) _rows; i++)
        for (int j = 0; j < (int) _cols; j++){
            if (_data[i][j] != m._data[i][j])
                return false;
        }
    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    for (int i = 0; i < (int) _rows; i++)
        for (int j = 0; j < (int) _cols; j++)
            _data[i][j] += m._data[i][j];
  return *this;
}

Matrix& Matrix::operator*=(int c) {
    for (int i = 0; i < (int) _rows; i++)
        for (int j = 0; j < (int) _cols; j++)
            _data[i][j] *= c;
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) { 
  *this += (m * -1);  
  return *this;
}

Matrix& Matrix::operator=(const Matrix& m) { 
  for (int i = 0; i < (int) _rows; i++)
      delete [] _data[i];
   delete []_data;
  
  _rows = m._rows;
  _cols = m._cols;
  _data = new int*[_rows];
  for (int i = 0; i < (int) _rows; i++){
      _data[i] = new int[_cols];
      for (int j = 0; j < int(_cols); j++)
          _data[i][j] = m._data[i][j];
  }
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  *this = (*this * m);
  return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
  Matrix tmp(_rows, _cols);
  tmp += m;
  tmp += *this;
  return tmp;
}

Matrix Matrix::operator*(int c) const{
  Matrix tmp(_rows, _cols);
  tmp += *this;
  tmp *= c;
  return tmp;
}

Matrix Matrix::operator-(const Matrix& m) const{
  Matrix tmp(m);
  tmp -= m;
  return tmp;
 }

Matrix Matrix::operator*(const Matrix& m) const{
  Matrix tmp(_rows, m._cols);
  for (int i = 0; i < (int) tmp._rows; i++)
    for (int j = 0; j < (int) tmp._cols; j++){
        tmp._data[i][j] = 0;
        for (int k = 0; k < (int) m._rows; k++)
            tmp._data[i][j] += _data[i][k]*m._data[k][j];
    }
  return tmp;
}
