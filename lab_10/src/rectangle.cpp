#include "rectangle.h"
#include <iostream> 
#include <cmath>

void Rectangle::print() const {
    std::cout << id << ": x = " << x << " y = " << y;
    std::cout << " width = " << width_ << " height = " << height_ << '\n';
}


bool Rectangle::is_inside(int x0, int y0) const {
    if (std::abs(x - x0) * 2 <= width_ && std::abs(y - y0) * 2 <= height_)
        return 1;
    return 0;
}

void Rectangle::zoom(int factor) {
    width_ *= factor;
    height_ *= factor;
}

