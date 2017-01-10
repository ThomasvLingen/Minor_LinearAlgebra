//
// Created by jazula on 11/30/16.
//

#ifndef LINEARALGEBRA_LINALMATRIX_HPP
#define LINEARALGEBRA_LINALMATRIX_HPP

#include <vector>
#include <cstddef>

using std::vector;

template <class T> class LinalMatrix {
public:
    LinalMatrix(const vector<vector<T>>& values);
    LinalMatrix();
    LinalMatrix(size_t y_size, size_t x_size);

    vector<vector<T>> values; // Y,X
    size_t y_size;
    size_t x_size;

    virtual LinalMatrix<T> operator*(const LinalMatrix<T>& other);

    static LinalMatrix<T> translation_matrix(T x, T y, T z);

    void print();

private:
};

#include "LinalMatrix.tpp"

#endif //LINEARALGEBRA_LINALMATRIX_HPP
