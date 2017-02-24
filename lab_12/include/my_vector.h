#include <cstddef>
#include <iostream>

#pragma once

template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(const my_vector& other);
    my_vector& operator=(const my_vector& other);
    ~my_vector();

    size_t size();//
    size_t capacity();//
    bool empty();

    void resize(size_t n);
    void reserve(size_t n);

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
    array_ = new T[capacity_];    
}


template <class T>
my_vector<T>::my_vector(size_t n) {
    capacity_ = 1;
    size_ = 0;
    while (capacity_ < n)
        capacity_ *= 2;
    array_ = new T[capacity_];    
}


template <class T>
my_vector<T>::~my_vector() {
    delete [] array_;
}


template <class T>
my_vector<T>::my_vector(const my_vector& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < size_; i++)
        array_[i] = other.array_[i];
}


template <class T>
my_vector<T>& my_vector<T>::operator= (const my_vector& other) {
    delete [] array_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < size_; i++)
        array_[i] = other.array_[i];        
    return *this;
}


template <class T>
size_t my_vector<T>::size() {
    return size_;
}


template <class T>
size_t my_vector<T>::capacity() {
    return capacity_;
}


template <class T>
bool my_vector<T>::empty() {
    return size_ == 0;
}


template <class T>
T& my_vector<T>::operator[] (size_t index) {
    return array_[index];
}


template <class T>
void my_vector<T>::resize(size_t size) {
    reserve(size);
    size_ = size;
}


template <class T>
void my_vector<T>::reserve(size_t capacity) {
    if (capacity <= capacity_)
        return;
    while (capacity_ < capacity)
        capacity_ *= 2;
    T* tmp = new T[capacity_];
    for (size_t i = 0; i < size_; i++)
        tmp[i] = array_[i];
    delete [] array_;
    array_ = tmp;
}


template <class T>
void my_vector<T>::push_back(const T& t) {
    resize(size_ + 1);
    array_[size_ - 1] = t;        
}


template <class T>
void my_vector<T>::pop_back() {
    size_--;
}


template <class T>
void my_vector<T>::clear() {
    size_ = 0;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const my_vector<T>& v) {
        for (size_t i = 0; i < v.size_; i++)
            os << v.array_[i] << ' ';
        return os;
}

