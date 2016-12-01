//
// Created by mafn on 11/30/16.
//

#include "LinalVector.hpp"
#include <iostream>
#include <assert.h>

LinalVector::LinalVector(int x, int y)
: LinalMatrix<int> (vector<vector<int>>{{x}, {y}})
{
}

LinalVector::LinalVector(LinalMatrix obj)
{
    assert(obj.x_size != 1 || obj.y_size != 2);
    LinalVector(obj.values[0][0], obj.values[1][0]);
}

//void LinalVector::multiply_by_factor(int factor)
//{
//    *this = *this * LinalVector(factor,factor);
//}
//
//LinalVector LinalVector::operator+(const LinalVector other)
//{
//    return LinalVector(this->dir_x + other.dir_x, this->dir_y + other.dir_y);
//}
//
//LinalVector LinalVector::operator*(const LinalVector other)
//{
//    return LinalVector(this->dir_x * other.dir_x, this->dir_y * other.dir_y);
//}
