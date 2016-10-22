#pragma once
#include <cstddef>

class MyVector{
private:
    int* array;
    std::size_t size_v;
    std::size_t capacity_v;
public:
    MyVector();
    MyVector(std::size_t init_capacity);
    ~MyVector();
    void resize(std::size_t new_size);
    void push_back(int value);
    void print();
    void set(size_t i, int value);
    void reserve(size_t new_capacity);
    int get(std::size_t i);
    std :: size_t size();
    std :: size_t capacity();
    void insert(std :: size_t i, int value);
    void erase(std :: size_t i);
};
