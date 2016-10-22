#include "../include/my_vector.h"

int main(){
    MyVector v(3);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.print();   
    v.erase(3);  
    v.erase(2);
    v.print();   
    v.insert(1, 0);   
    v.insert(3, 8);
    v.print();
    MyVector v1;
    v1.reserve(6);
    v1.resize(3);
    v1.print();
    v1.set(2, 10);
    int a = v1.get(2);
    v1.resize(a);
    v1.print();
    return 0;
}
