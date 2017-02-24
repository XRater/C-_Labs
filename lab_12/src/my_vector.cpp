#include <my_vector.h>
#include <cstddef>

/*
template <class T>
my_vector<T>::my_vector(size_t n) {
    size_t capacity_ = 1;
    while (capacity_ < n)
        capacity_ *= 2;
    array_ = new T[capacity_];    
}


template <class T>
my_vector<T>::~my_vector() {
    delete [] array_;
}
*/
/*
template <class T>
my_vector<T>::my_vector(my_vector& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    array_ = new T[capacity_];
    for (int i = 0; i < size_; i++)
        array_[i] = other.array_[i];
}


template <class T>
my_vector<T>& my_vector<T>::operator= (my_vector& other) {
    delete array_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    array_ = new T[capacity_];
    for (int i = 0; i < size_; i++)
        array_[i] = other.array_[i];        
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

*/
