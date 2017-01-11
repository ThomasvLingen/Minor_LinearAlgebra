//
// Created by jazula on 11/30/16.
//

#ifndef LINEARALGEBRA_LINALMATRIX_HPP
#define LINEARALGEBRA_LINALMATRIX_HPP

#include <vector>
#include <cstddef>
#include "Axis.hpp"

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

    LinalMatrix<T> average_column();

    static LinalMatrix<T> identity_matrix();

    static LinalMatrix<T> translation_matrix(T x, T y, T z);

    static LinalMatrix<T> rotate_matrix(Axis axis, int degrees, T x, T y, T z);
    static LinalMatrix<T> rotate_matrix(Axis axis, int degrees, LinalMatrix<T> rotation_point);
    static LinalMatrix<T> rotate_matrix(Axis axis, int degrees);

    void print();

private:
    static LinalMatrix<T> _get_rotation_matrix(Axis axis, int degrees);
};

#include "LinalMatrix.tpp"

#endif //LINEARALGEBRA_LINALMATRIX_HPP
