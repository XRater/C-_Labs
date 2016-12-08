#include "circle.h"
#include <cstring>
#include <iostream>

Circle::Circle(int id, int x, int y, int radius, const char* label)
        : Figure(id, x, y), radius_(radius) {
    char* label_ptr = new char[strlen(label) + 1];
    strcpy(label_ptr, label);
    label_ = label_ptr;            
};

Circle::~Circle() {
    delete [] label_;
}


void Circle::print() const {
    std::cout << id << ": x = " << x << " y = " << y;
    std::cout << " radius = " << radius_ << " label = " << label_ << '\n';
}


bool Circle::is_inside(int x0, int y0) const {
    if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= radius_ * radius_)
        return 1;
    return 0;
}


void Circle::zoom(int factor) {
    radius_ *= factor;
}
