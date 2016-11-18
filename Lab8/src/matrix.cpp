#include "../include/matrix.h"
#include <algorithm>
#include <cstdio>

using namespace std;

Matrix::Matrix(size_t r, size_t c) {
    _rows = r;
    _cols = c;
    _data = new int*[_rows];
    for (size_t i = 0; i < _rows; i++)
        _data[i] = new int[_cols]();
}

Matrix::Matrix(const Matrix &that){
    _rows = that._rows;
    _cols = that._cols;
    _data = new int*[_rows];
    for (size_t i = 0; i < _rows; i++)
        _data[i] = new int[_cols];
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
    for (size_t i = 0; i < _rows; i++)
        delete []_data[i];
    delete []_data;
}

size_t Matrix::get_rows() const{ return _rows; }
size_t Matrix::get_cols() const{ return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const{
    return _data[i][j];
}

void Matrix::print(FILE* f) const{
    for (size_t i = 0; i < _rows; i++){
        for (size_t j = 0; j < _cols; j++)
            fprintf(f, "%d ", _data[i][j]);
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(const Matrix& m) const{
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
            if (_data[i][j] != m._data[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& m) const{
    return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
                _data[i][j] += m._data[i][j];
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _cols; j++)
                _data[i][j] -= m._data[i][j];
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    return *this = *this * m;
}

const Matrix Matrix::operator+(const Matrix& m) const{
    Matrix tmp(m);
    tmp += (*this);
    return tmp;
}

const Matrix Matrix::operator-(const Matrix& m) const{
    Matrix tmp(m);
    tmp -= (*this);
    return tmp;
    return *this;
}

const Matrix Matrix::operator*(const Matrix& m) const{
    Matrix tmp(_rows, m._cols);
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < m._cols; j++)
            for (size_t k = 0; k < _cols; k++)
                tmp._data[i][j] += _data[i][k] * m._data[k][j];
    return tmp;
}
