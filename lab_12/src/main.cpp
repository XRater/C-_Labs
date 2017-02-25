#include <iostream>
#include <string.h>

#include "my_vector.h"

class Product {
public:
    Product(const char* name = NULL, int quantity = 0, double price = 0);
    Product(const Product& other);
    ~Product();

    Product& operator=(const Product& other);
   
    friend std::ostream& operator<<(std::ostream& os, const Product& p);    
private:
    char *name_;
    int quantity_;
    double price_;
};

Product::Product(const char* name, int quantity, double price) {
    name_ = NULL;
    if (name != NULL) {
        name_ = new char[strlen(name) + 1];
        strcpy(name_, name);
    }
    quantity_ = quantity;
    price_ = price;
}

Product::Product(const Product& other) {
    name_ = NULL;
    if (other.name_ != NULL) {
        name_ = new char[strlen(other.name_) + 1];
        strcpy(name_, other.name_);
    }
    quantity_ = other.quantity_;
    price_ = other.price_;    
}

Product& Product::operator=(const Product& other) {
    Product tmp(other);
    std::swap(name_, tmp.name_);
    std::swap(quantity_, tmp.quantity_);
    std::swap(price_, tmp.price_);
    return *this;
}



Product::~Product() {
    delete [] name_;
}


std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << p.name_ << ' ' << p.quantity_ << ' ' << p.price_ ;
    return os;
}


void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}

//-------------------------------------------------------------------------------------------------------

template<class T>
void test_my_vector(const T& t1, const T& t2) {
  
    my_vector<T> v1;
    std::cout << v1.size() << ' ' << v1.capacity() << ' ' << v1.empty() << '\n';
    v1.push_back(t1);
    v1.push_back(t2);
    v1.pop_back();
    std::cout << v1.size() << ' ' << v1.capacity() << ' ' << v1.empty() << '\n';
    std::cout << v1 << '\n';
  
    my_vector<T> v2(2);
    v2.resize(2);
    v2[0] = t2;
    v2[1] = t1;
    std::cout << v2.size() << ' ' << v2.capacity() << ' ' << v2.empty() << '\n';
    std::cout << v2 << '\n';
    

    my_vector<T> v3(v2);    
    v3[0] = v3[1];
    std::cout << v3.size() << ' ' << v3.capacity() << ' ' << v3.empty() << '\n';
    std::cout << v3 << '\n';
    v3.resize(3);
    v3[2] = t1;
    v3.reserve(10);   
    std::cout << v3.size() << ' ' << v3.capacity() << ' ' << v3.empty() << '\n';
    std::cout << v3 << '\n';
    v3 = v1;
    v3.clear();
    std::cout << v3.size() << ' ' << v3.capacity() << ' ' << v3.empty() << '\n';
    std::cout << v3 << '\n';
    std::cout << "\n\n"; 
    
}


int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));    
    return 0;
}



