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

template<typename T, typename F>
class where_enumerator;


template<typename T>
class enumerator {
public:
    virtual const T& operator*() const = 0; // Получает текущий элемент.
    virtual enumerator& operator++() = 0;  // Переход к следующему элементу
    virtual operator bool() const = 0;  // Возвращает true, если есть текущий элемент


    auto drop(int count) {
        return drop_enumerator<T>(*this, count);
    }    

    auto take(int count) {
        return take_enumerator<T>(*this, count);
    }    

    template<typename U = T, typename F>
    auto select(F func) {
        return select_enumerator<U, T, F>(*this, func);            
    }

    auto until_eq(const T& t) {
        return until([&t](const T& elem)->bool{ return elem == t; });
    }

    template<typename F>
    auto until(F func) {
        return until_enumerator<T, F>(*this, func);
    }

    auto where_neq(const T& t) {
        return where([&t](const T& elem)->bool{ return elem != t; });
    }

    template<typename F>
    auto where(F func) {
        return where_enumerator<T, F>(*this, func);
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
       
    const T& operator *() const override { return *begin_; }
  
    range_enumerator& operator++() override {
        if (begin_ != end_)
            ++begin_;

        return *this;
    } 
   
    operator bool() const override { return begin_ != end_; }

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
     
    const T& operator*() const override { return *parent_; }

    drop_enumerator<T>& operator++() override { 
        ++parent_; 
        return *this;
    }

    operator bool() const override { return parent_; }

private:
    enumerator<T>& parent_;
};



template<typename T>
class take_enumerator : public enumerator<T> {
public:
    take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

    const T& operator *() const override { return *parent_; }

    take_enumerator<T>& operator++() override { 
        if (--count_ >= 0) {
            ++parent_; 
            return *this;
        }
        else
            throw EnumeratorException("Out of elements");
    }

    operator bool() const override { return count_ > 0 && parent_; }

private:
    enumerator<T>& parent_;
    int count_;
};


template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
    select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(func) {}
    ~select_enumerator() {delete accum;}
    
/*
    We could also hold T instead of T* (we wont allocate a lot of memory in this case)
    But with this way (holding T*) we are able to work with classes without defaul constructor (NonConstructable in tests)
*/    
    const T& operator*() const override {
        delete accum;
        accum = new T(func_(*parent_));
        return *accum;
    }
        
    select_enumerator& operator++() override {
        ++parent_;
        return *this;    
    }
    
    operator bool() const override { return parent_; }

private:
    enumerator<U>& parent_;    
    mutable F func_;

    mutable T* accum = nullptr; 
};


template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
    until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(predicate) {}

    const T& operator*() const override { return *parent_; }
    
    until_enumerator& operator++() override {
        ++parent_;
        return *this;    
    }
    
    operator bool() const override { return parent_ && !predicate_(*parent_); }
    
private:
    enumerator<T>& parent_;
    mutable F predicate_;
};


template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
    where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(predicate) {
        if (parent_ && !predicate(*parent_))
            ++*this;
    }

    const T& operator*() const override { return *parent_; }
    
    where_enumerator& operator++() override {
        ++parent_;
        while (parent_ && !predicate_(*parent_))
            ++parent_;
        return *this;
    }
    
    operator bool() const override { return parent_; }
    
private:
    enumerator<T>& parent_;
    mutable F predicate_;
};

#endif
