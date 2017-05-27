#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <type_traits>

class EnumeratorException : public std::logic_error {
public:
    EnumeratorException(std::string msg) : logic_error(msg) {};
};


template<typename T, typename Iter>
class range_enumerator;

template<typename T>
class drop_enumerator;

template<typename T, typename U, typename F>
class select_enumerator;

template<typename T>
class take_enumerator;

template<typename T, typename F>
class until_enumerator;


template<typename T>
class enumerator {
public:
    virtual const T& operator*() const = 0; // Получает текущий элемент.
    virtual enumerator& operator++() = 0;  // Переход к следующему элементу
    virtual operator bool() const = 0;  // Возвращает true, если есть текущий элемент


    auto drop(int count) {
        return drop_enumerator<T>(*this, count);
    }    

    template<typename U = T, typename F>
    auto select(F func) {
        return select_enumerator<U, T, F>(*this, func);            
    }

    auto take(int count) {
        return take_enumerator<T>(*this, count);
    }    

    template<typename F>
    auto until(F func) {
        return until_enumerator<T, F>(*this, func);
    }

    std::vector<T> to_vector() {
        std::vector<T> tmp;
        while (*this) {
            tmp.push_back(**this);
            ++*this;
        }
        return tmp;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        while (*this) {
            *it = **this;
            ++*this, ++it;
        }
    }
};

template<typename T>
auto from(T begin, T end) {
    typedef typename std::decay<decltype(*begin)>::type T_val;
    return range_enumerator<T_val, T>(begin, end);
}


template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}
    
    operator bool() const {
        return begin_ != end_;
    }
    
    const T& operator *() const {
        if (begin_ == end_)
            throw EnumeratorException("Bad iterator");
        return *begin_;
    }
  
    range_enumerator& operator++() {
        if (begin_ == end_)
            throw EnumeratorException("Bad iterator");
        ++begin_;
        return *this;
    } 

private:
    Iter begin_, end_;
};



template<typename T>
class drop_enumerator : public enumerator<T> {
public:
    drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
        for (int i = 0; i < count; i++)
            ++*this; 
    }

    operator bool() const { 
        return parent_; 
    }
    
    const T& operator*() const { 
        return *parent_; 
    }

    drop_enumerator<T>& operator++() { 
        ++parent_; 
        return *this;
    }

private:
    enumerator<T>& parent_;
};



template<typename T>
class take_enumerator : public enumerator<T> {
public:
    take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

    operator bool() const { return count_ > 0 && parent_; }

    const T& operator *() const { return *parent_; }

    take_enumerator<T>& operator++() { 
        if (--count_ >= 0) {
            ++parent_; 
            return *this;
        }
        else
            throw EnumeratorException("Out of elements");
    }

private:
    enumerator<T>& parent_;
    int count_;
};


template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
    select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(func) {
        if (parent_)
            accum = new T(func_(*parent_));
    }
    ~select_enumerator() {delete accum;}
    
    const T& operator*() const {
        return *accum;
    }
        
    select_enumerator& operator++() {
        ++parent_;
        if (parent_) {
            delete accum;
            accum = new T(func_(*parent_));
        }
        return *this;    
    }
    
    operator bool() const {
        return parent_; 
    }

private:
    enumerator<U>& parent_;    
    mutable F func_;

    mutable T* accum = nullptr; 
};


template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
    until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(predicate) {}

    const T& operator*() const {
        return *parent_;
    }
    
    until_enumerator& operator++() {
        ++parent_;
        return *this;    
    }
    
    operator bool() const {
        return parent_ && !predicate_(*parent_); 
    }
    
private:
    enumerator<T>& parent_;
    mutable F predicate_;
};

#endif
