#include <cassert>
#include <stdint.h>
#include <cstdio>
 
#pragma once 
template <typename T, size_t N>
class my_array {
public:
    const T& at(size_t index) const;
    T& at(size_t index);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    bool empty() const;
    size_t size() const;

    void fill(T val);
private:
    T array_[N];
};

template <size_t N>
class my_array<bool, N> {
public:
    class Proxy {
    public:
        Proxy(uint8_t* ptr, size_t ind) : ptr_(ptr), ind_(ind) {};    
    
        operator bool() const; 
        Proxy& operator=(bool other);
        Proxy& operator=(const Proxy& other);
    private:
        uint8_t* ptr_;
        size_t ind_;
    };

    const bool at(size_t index) const;
    Proxy at(size_t index);
    Proxy operator[](size_t index);
    const bool operator[](size_t index) const;

    bool empty() const;
    size_t size() const;

    void fill(bool val);
private:
    uint8_t array_[(N + 7) / 8];
};

//-------------------------------------------------------------------------------------------------------------------

template <typename T, size_t N>
bool my_array<T, N>::empty() const{
    return N == 0;
}


template <typename T, size_t N>
const T& my_array<T, N>::at(size_t index) const{
    assert(index >= 0 && index < N);    
    return array_[index];
}


template <typename T, size_t N>
T& my_array<T, N>::at(size_t index) {
    assert(index >= 0 && index < N);    
    return array_[index];
}


template <typename T, size_t N>
T& my_array<T, N>::operator[] (size_t index) {
    return array_[index];
}


template <typename T, size_t N>
const T& my_array<T, N>::operator[] (size_t index) const{
    return array_[index];
}


template <typename T, size_t N>
size_t my_array<T, N>::size() const{
    return N;
}


template <typename T, size_t N>
void my_array<T, N>::fill(T val) {
    for (size_t i = 0; i < N; i++)
        array_[i] = val;
}



template <size_t N>
my_array<bool, N>::Proxy::operator bool() const {
    return (bool) (*ptr_ & (1 << ind_));
}

template <size_t N>
typename my_array<bool, N>:: Proxy& my_array<bool, N>::Proxy::operator=(bool other) {
    *ptr_ = ((*ptr_) & (~(1 << ind_))) | (other << ind_);
    return *this; 
}


template <size_t N>
typename my_array<bool, N>:: Proxy& my_array<bool, N>::Proxy::operator=(const Proxy& other) {
    bool tmp = (bool) other;
    *this = tmp;
    return *this; 
}


template <size_t N>
bool my_array<bool, N>::empty() const{
    return N == 0;
}


template <size_t N>
const bool my_array<bool, N>::at(size_t index) const{
    assert(index >= 0 && index < N);    
    return (bool) (array_[index / 8] & (1 << (index % 8)));
}


template <size_t N>
typename my_array<bool, N>::Proxy my_array<bool, N>::at(size_t index) {
    assert(index >= 0 && index < N);    
    return Proxy(array_ + index/8, index % 8);
}


template <size_t N>
typename my_array<bool, N>::Proxy my_array<bool, N>::operator[] (size_t index) {
    return Proxy(array_ + index/8, index % 8);
}


template <size_t N>
const bool my_array<bool, N>::operator[] (size_t index) const{
    return (bool) (array_[index / 8] & (1 << (index % 8)));
}


template <size_t N>
size_t my_array<bool, N>::size() const{
    return N;
}


template <size_t N>
void my_array<bool, N>::fill(bool val) {
    val = val == true ? 1 : 0;
    for (size_t i = 0; i < N; i++) {
        this->operator[](i) = val;
    }
}


