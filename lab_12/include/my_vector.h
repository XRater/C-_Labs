#include <cstddef>
#include <iostream>
#include <utility>

#pragma once

template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(const my_vector& other);
    my_vector& operator=(const my_vector& other);
    ~my_vector();
    
    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    void resize(size_t n);
    void reserve(size_t n);

    T& operator[](size_t index) const;
    T& operator[](size_t index);

    void push_back(const T& t);
    void pop_back();
    void clear();

    template <class T1>
    friend std::ostream& operator<<(std::ostream& os, const my_vector<T1>& v); 
   
private:
    size_t capacity_;
    size_t size_;
    T* array_;
};

//-----------------------------------------------------------------------------------------------------

template <class T>
my_vector<T>::my_vector() {
    capacity_ = 2;
    size_ = 0;
    array_ = (T*)(new char[capacity_ * sizeof(T)]);    
}


template <class T>
my_vector<T>::my_vector(size_t n) {
    capacity_ = 1;
    size_ = 0;
    while (capacity_ < n)
        capacity_ *= 2;
    array_ = (T*)(new char[capacity_ * sizeof(T)]);    
}


template <class T>
my_vector<T>::~my_vector() {
    for (size_t i = 0; i < size_; i++)        
        array_[i].~T();
    delete [] (char*) array_;
}


template <class T>
my_vector<T>::my_vector(const my_vector& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    array_ = (T*)(new char[capacity_ * sizeof(T)]);
    for (size_t i = 0; i < size_; i++)
        new (&array_[i]) T(other.array_[i]);
}


template <class T>
my_vector<T>& my_vector<T>::operator= (const my_vector& other) {
    my_vector<T> tmp(other);
    std::swap(array_, tmp.array_);
    std::swap(size_, tmp.size_);
    std::swap(capacity_, tmp.capacity_);
    return *this;
}


template <class T>
size_t my_vector<T>::size() const {
    return size_;
}


template <class T>
size_t my_vector<T>::capacity() const {
    return capacity_;
}


template <class T>
bool my_vector<T>::empty() const {
    return size_ == 0;
}


template <class T>
T& my_vector<T>::operator[] (size_t index) {
    return array_[index];
}


template <class T>
T& my_vector<T>::operator[] (size_t index) const {
    return array_[index];
}


template <class T>
void my_vector<T>::resize(size_t size) {
    reserve(size);
    for (size_t i = size_; i < size; i++)
        new (&array_[i]) T();
    for (size_t i = size; i < size_; i++)
        array_[i].~T();
        
    size_ = size;
}


template <class T>
void my_vector<T>::reserve(size_t capacity) {
    if (capacity <= capacity_)
        return;
    while (capacity_ < capacity)
        capacity_ *= 2;
    T* tmp = (T*)(new char[capacity_ * sizeof(T)]);    
    for (size_t i = 0; i < size_; i++)
        new (&tmp[i]) T(array_[i]);
    this->~my_vector();    
    array_ = tmp;
}


template <class T>
void my_vector<T>::push_back(const T& t) {
    resize(size_ + 1);
    new (&array_[size_ - 1]) T(t);        
}


template <class T>
void my_vector<T>::pop_back() {
    array_[--size_].~T();
}


template <class T>
void my_vector<T>::clear() {
    for (size_t i = 0; i < size_; i++)
        array_[i].~T();
    size_ = 0;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const my_vector<T>& v) {
    for (size_t i = 0; i < v.size_; i++)
       os << v.array_[i] << ' ';
    return os;
}
    
