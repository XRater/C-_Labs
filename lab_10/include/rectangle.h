#include "figure.h"

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height)
     : Figure(id, x, y), width_(width), height_(height) {};
    ~Rectangle() {};

    void print() const;
    bool is_inside(int x, int y) const;
    virtual void zoom(int factor);

private:
    int width_;
    int height_;
};
