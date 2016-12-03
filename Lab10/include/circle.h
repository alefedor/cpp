#pragma once

#include "figure.h"

class Circle : public Figure {
  public:
    Circle(int id, int x, int y, int radius, const char* l);
    void print() const;
    bool is_inside(int x, int y) const;
    void zoom(int factor);
    ~Circle();
  protected:
    int radius;
    char *label;
};
