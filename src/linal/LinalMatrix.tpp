//
// Created by jazula on 11/30/16.
//

#include <iostream>
#include "LinalMatrix.hpp"
#include "../DegreeUtil.hpp"
#include <cmath>
#include "Axis.hpp"

template <class T>
LinalMatrix<T>::LinalMatrix(const vector<vector<T>>& values)
: values(values)
, y_size(values.size())
, x_size((y_size > 0) ? values[0].size() : 0)
{
}

template <class T>
LinalMatrix<T>::LinalMatrix()
: y_size(0)
, x_size(0)
{}

template <class T>
LinalMatrix<T>::LinalMatrix(size_t y_size, size_t x_size)
: y_size(y_size)
, x_size(x_size)
{
    values.resize(y_size);
    for(auto& x_vector : values){
        x_vector.resize(x_size);
    }
}

template <class T>
LinalMatrix<T> LinalMatrix<T>::operator*(const LinalMatrix<T>& other)
{
    if(this->x_size != other.y_size) {
        std::cout << "Invalid matrix multiplication" << std::endl;
        std::cout << "x: " << this->x_size << " y: " << this->y_size << std::endl;
        std::cout << "and" << std::endl;
        std::cout << "x: " << other.x_size << " y: " << other.y_size << std::endl;

        return *this;
        // perhaps this is a bit hacky, should throw an exception, but lets just return the original for now
    }

    LinalMatrix<T> new_matrix(this->y_size, other.x_size);

    for (size_t y = 0; y < new_matrix.y_size; y++) { //just end my life already
        for (size_t x = 0; x < new_matrix.x_size; x++) {
            for (size_t multi = 0; multi < new_matrix.y_size; multi++) {
                new_matrix.values[y][x] += this->values[y][multi] * other.values[multi][x];
            }
        }
    }

    return new_matrix;
}

template <class T>
void LinalMatrix<T>::print()
{
    std::cout << "----" << std::endl;
    for(auto& row : this->values){
        std::cout << "[ ";
        for(auto val : row){
            std::cout << val << " ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "----" << std::endl;
}

template <class T>
LinalMatrix<T> LinalMatrix<T>::translation_matrix(T x, T y, T z)
{
    return LinalMatrix<T>({
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    });
}

template <class T>
LinalMatrix<T> LinalMatrix<T>::rotate_matrix(Axis axis, int degrees, T x, T y, T z)
{
    // move to origin
    LinalMatrix origin_matrix = LinalMatrix::translation_matrix(-x, -y, -z);
    // rotate using the rotate matrix (perhaps get the matrix from a function)
    LinalMatrix rotation_matrix = LinalMatrix::_get_rotation_matrix(axis, degrees);
    // move back to old position
    LinalMatrix original_position = LinalMatrix::translation_matrix(x, y, z);

    return origin_matrix * rotation_matrix * original_position;
}

template <class T>
LinalMatrix<T> LinalMatrix<T>::rotate_matrix(Axis axis, int degrees, LinalMatrix<T> rotation_point)
{
    return LinalMatrix<T>::rotate_matrix(
        axis,
        degrees,
        -rotation_point.values[0][0],
        -rotation_point.values[1][0],
        -rotation_point.values[2][0]
    );
}

template <class T>
LinalMatrix<T> LinalMatrix<T>::rotate_matrix(Axis axis, int degrees)
{
    return LinalMatrix::_get_rotation_matrix(axis, degrees);
}

template <class T>
LinalMatrix<T> LinalMatrix<T>::_get_rotation_matrix(Axis axis, int degrees)
{
    double rad = DegreeUtil::degree_to_radian(degrees);
    switch (axis) {
        case Axis::x :
            return LinalMatrix<T> ({
                {1, 0,        0,         0},
                {0, cos(rad), -sin(rad), 0},
                {0, sin(rad), cos(rad),  0},
                {0, 0,        0,         1}
            });
        case Axis::y :
            return LinalMatrix<T> ({
                {cos(rad),  0, sin(rad), 0},
                {0,         1, 0,        0},
                {-sin(rad), 0, cos(rad), 0},
                {0,         0, 0,        1}
            });
        case Axis::z :
            return LinalMatrix<T> ({
                {cos(rad), -sin(rad), 0, 0},
                {sin(rad), cos(rad),  0, 0},
                {0,        0,         1, 0},
                {0,        0,         0, 1}
            });
        default:
            throw "You dun goofed, using a non valid Axis";
    }
}

template <class T>
LinalMatrix<T> LinalMatrix<T>::average_column()
{
    vector<vector<T>> average;

    for (vector<T> row : this->values) {
        T row_total = 0;
        average.push_back(vector<T>());
        for (T value : row) {
            row_total += value;
        }
        average.back().push_back(row_total/row.size());
    }

    return average; //implicit conversion
}
