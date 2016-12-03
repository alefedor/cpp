#include "scheme.h"
#include <algorithm>
#include <utility>

Scheme::Scheme(int capacity){
    size_ = 0;
    figures_ = new Figure* [capacity];
}

Scheme::~Scheme(){
    for (int i = 0; i < size_; i++)
        delete figures_[i];
    delete []figures_;
}

void Scheme::push_back_figure(Figure* fg){
    figures_[size_] = fg;
    size_++;
}

void Scheme::remove_figure(int id){
    int pos = 0;
    for (; pos < size_; pos++)
        if (figures_[pos] -> get_id() == id)
            break;
    if (pos == size_)
        return;
    for (int i = pos; i + 1 < size_; i++)
        std::swap(figures_[i], figures_[i+1]);
    size_--;
    delete figures_[size_];
}

void Scheme::print_all_figures(){
    for (int i = 0; i < size_; i++){
        figures_[i] -> print();
    }
}

void Scheme::zoom_figure(int id, int factor){
    for (int i = 0; i < size_; i++)
        if (figures_[i] -> get_id() == id)
            figures_[i] -> zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y){
    for (int i = 0; i < size_; i++)
        if (figures_[i] -> is_inside(x, y))
            return figures_[i];
    return NULL;
}

void Scheme::move(int id, int new_x, int new_y){
    for (int i = 0; i < size_; i++)
        if (figures_[i] -> get_id() == id)
            figures_[i] -> move(new_x, new_y);
}
