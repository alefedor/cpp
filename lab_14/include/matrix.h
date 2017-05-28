#ifndef MATRIX_H_
#define MATRIX_H_

#include <string>
#include <cstdio>
#include <cstddef>

class MatrixException{
public:
    MatrixException(const char* s);
    const char* what() const;

private:
    std::string _data;
};

class Matrix{
public:
    Matrix();
    Matrix(std::size_t r, std::size_t c);
    Matrix(const Matrix& that);
    ~Matrix();
    int get(int i, int j) const;
    friend std::ostream& operator << (std::ostream& os, const Matrix &a);
    void load(const char *file);

    Matrix& operator=(const Matrix& m);
    Matrix& operator+=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);

private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
    void swap_matrix(Matrix &m);
    void malloc(size_t r, size_t c);
};

#endif
