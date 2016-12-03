#include "rectangle.h"
#include <cstring>
#include <cstdio>
#include <cmath>

Rectangle::Rectangle(int id, int x, int y, int width, int height):Figure(id, x, y), width(width), height(height){}

void Rectangle::print() const{
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int sx, int sy) const{
    return (2 * x - width <= 2 * sx  && 2 * sx <= 2 * x + width && 2 * y - height <= 2 * sy && 2 * sy <= 2 * y + height);
}

void Rectangle::zoom(int factor){
    width *= factor;
    height *= factor;
}

Rectangle::~Rectangle(){}

