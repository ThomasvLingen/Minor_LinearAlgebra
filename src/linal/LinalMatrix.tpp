//
// Created by jazula on 11/30/16.
//

#include <iostream>
#include "LinalMatrix.hpp"

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
        return *this;
        // perhaps this is a bit hacky, should throw an exception, but lets just return the original for now
    }

    LinalMatrix<T> new_matrix(this->y_size, other.x_size);

    for (int y = 0; y < new_matrix.y_size; y++) { //just end my life already
        for (int x = 0; x < new_matrix.x_size; x++) {
            for (int multi = 0; multi < new_matrix.y_size; multi++) {
                new_matrix.values[y][x] += this->values[y][multi] * other.values[multi][x];
            }
        }
    }

    return new_matrix;
}

template <class T>
void LinalMatrix<T>::print()
{
    for(auto& row : this->values){
        for(auto val : row){
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}
