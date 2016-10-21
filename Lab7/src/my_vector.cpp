#include "../include/my_vector.h"
#include <cassert>
#include <algorithm>
#include <utility>

using namespace std;

MyVector::MyVector(){
    _data = new int[2];
    _cp = 2;
    _sz = 0;
}

MyVector::MyVector(size_t init_capacity){
    _data = new int[init_capacity];
    _cp = init_capacity;
    _sz = 0;
}

MyVector::~MyVector(){
    delete []_data;
}

void MyVector::set(size_t index, int value){
    assert (index < _sz && "Set range error");
    _data[index] = value;
}

int MyVector::get(size_t i){
    assert (i < _sz && "Get range error");
    return _data[i];
}

size_t MyVector::size(){
    return _sz;
}

size_t MyVector::capacity(){
    return _cp;
}

void MyVector::push_back(int value){
    if (_sz == _cp){
        _cp *= 2;
        int *new_v = new int[_cp];
        for (size_t i = 0; i < _sz; i++)
            new_v[i] = _data[i];
        swap(new_v, _data);
        delete []new_v;
    }
    _data[_sz++] = value;
}

void MyVector::reserve(size_t new_capacity){
    if (_cp >= new_capacity)
        return;
    _cp = new_capacity;
    int *new_v = new int[new_capacity];
    for (size_t i = 0; i < _sz; i++)
        new_v[i] = _data[i];
    swap(new_v, _data);
    delete []new_v;
}

void MyVector::resize(size_t new_size){
    if (new_size <= _sz){
        _sz = new_size;
        return;
    }
    for (size_t i = _sz; i < new_size; i++)
        this -> push_back(0);
}

void MyVector::insert(size_t index, int value){
    assert (index <= _sz && "Insert range error");
    int x = value;
    for (size_t i = index; i < _sz; i++)
        swap(x, _data[i]);
    this -> push_back(x);
}

void MyVector::erase(size_t index){
    assert (index < _sz && "Erase range error");
    int x;
    for (size_t i = _sz - 1; i >= index; i--)
        swap(x, _data[i]);
    _sz--;
}
