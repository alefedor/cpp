#include "circle.h"
#include <cstring>
#include <cstdio>
#include <cmath>

Circle::Circle(int id, int x, int y, int r, const char* l):Figure(id, x, y){
    radius = r;
    label = new char[strlen(l)+1];
    strcpy(label, l);
}

void Circle::print() const{
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

bool Circle::is_inside(int sx, int sy) const{
    return (sqrt((sx-x)*(double)(sx-x) + (sy-y)*(double)(sy-y)) <= radius);
}

void Circle::zoom(int factor){
    radius *= factor;
}

Circle::~Circle(){
    delete []label;
}
