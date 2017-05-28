#include "matrix.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

MatrixException::MatrixException(const char* s):_data(s){}

const char* MatrixException::what() const{
    return _data.c_str();
}

void Matrix::malloc(size_t r, size_t c){
    _rows = r;
    _cols = c;
    if (r > 0 && c > 0){
        _data = new int*[_rows];
        for (size_t i = 0; i < _rows; i++)
            _data[i] = new int[_cols]();
    }else
        _data = NULL;
}

Matrix::Matrix(){
    malloc(0, 0);
}

Matrix::Matrix(size_t r, size_t c){
    malloc(r, c);
}

Matrix::Matrix(const Matrix &that){
    malloc(that._rows, that._cols);
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            _data[i][j] = that._data[i][j];
}

void Matrix::swap_matrix(Matrix &m){
    swap(_rows, m._rows);
    swap(_cols, m._cols);
    swap(_data, m._data);
}

Matrix& Matrix::operator=(const Matrix& m){
    if (&m == this)
        return *this;
    Matrix(m).swap_matrix(*this);
    return *this;
}

Matrix::~Matrix(){
    if (_data){
        for (size_t i = 0; i < _rows; i++)
            delete []_data[i];
        delete []_data;
    }
}

int Matrix::get(int i, int j) const{
    if (i < 0 || i >= _rows || j < 0 || j >= _cols)
        throw MatrixException("ACCESS: bad index.");
    return _data[i][j];
}

std::ostream& operator << (std::ostream& os, const Matrix &a){
    for (size_t i = 0; i < a._rows; i++){
        for (size_t j = 0; j < a._cols; j++)
            os << a._data[i][j] << " ";
        if (i != a._rows - 1)
            os << "\n";
    }
    return os;
}

void Matrix::load(const char *file){
    ifstream in(file);
    size_t r, c;
    in >> r >> c;
    Matrix tmp(r, c);
    for (size_t i = 0; i < r; i++)
        for (size_t j = 0; j < c; j++)
            in >> tmp._data[i][j];
    swap_matrix(tmp);
}

Matrix& Matrix::operator+=(const Matrix& m){
    if (_rows != m._rows || _cols != m._cols)
        throw MatrixException("ADD: dimensions do not match.");
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
                _data[i][j] += m._data[i][j];
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m){
    if (_cols != m._rows)
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix tmp(_rows, m._cols);
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < m._cols; j++)
            for (size_t k = 0; k < _cols; k++)
                tmp._data[i][j] += _data[i][k] * m._data[k][j];
    swap_matrix(tmp);
    return *this;
}
