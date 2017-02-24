#include <iostream>
#include <string.h>

#include "my_vector.h"

class Product {
public:
    Product(const char* name = "", int quantity = 0, double price = 0);
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
    name_ = new char[strlen(name) + 1];
    strcpy(name_, name);
    quantity_ = quantity;
    price_ = price;
}

Product::Product(const Product& other) {
    name_ = new char[strlen(other.name_) + 1];
    strcpy(name_, other.name_);
    quantity_ = other.quantity_;
    price_ = other.price_;    
}

Product& Product::operator=(const Product& other) {
    delete [] name_;
    name_ = new char[strlen(other.name_) + 1];
    strcpy(name_, other.name_);
    quantity_ = other.quantity_;
    price_ = other.price_;    
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

int main() {
    //test_my_vector<int>(5, 10);
    //test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));
 //   my_vector<int> v1;
 //   v1.push_back(1);
 //   v1.push_back(2);
 //   v1.pop_back();
 //   v1.push_back(3);
  //  my_vector<int> u(5);
    my_vector<Product> v1(5);
    Product p("HI", 1, 1.2);
    Product p1(p);
    Product p2("Hello", 1, 1.2);
    //std::cout << p;
    //v1.resize(20);
    v1.push_back(p);
    v1.push_back(p2);
    v1.push_back(p1);
    my_vector<Product> v2;
    v2 = v1;
    
/*    std::cout << v.size() << ' ' << v.capacity() << ' ' << v.empty() << '\n';
    v = u;
    std::cout << v.size() << ' ' << v.capacity() << ' ' << v.empty() << '\n';
    my_vector<int> v1(v);   
    v1.push_back(1); */
    //std::cout << v1.size() << ' ' << v1.capacity() << ' ' << v1.empty() << '\n';
    //std::cout << v2[0] << ' ' << v2[1] << '\n';
    std::cout << v2;
    return 0;
}

