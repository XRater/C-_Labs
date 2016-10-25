#include "../include/my_vector.h"

int main(){
    MyVector v(3);
    v.resize(5);
    v.resize(7);
    v.resize(21);
    v.reserve(10);
    v.print();
    return 0;
}
