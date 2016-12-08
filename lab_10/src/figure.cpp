#include "figure.h"


void Figure::move(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

int Figure::getId() {
    return id;
}
