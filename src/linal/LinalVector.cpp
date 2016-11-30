//
// Created by mafn on 11/30/16.
//

#include "LinalVector.hpp"
#include <iostream>

LinalVector::LinalVector(int x, int y)
: dir_x(x)
, dir_y(y)
{
}

void LinalVector::multiply_by_factor(int factor)
{
    *this = *this * LinalVector(factor,factor);
}

void LinalVector::print()
{
    std::cout << "[" << this->dir_x << "," << this->dir_y << "]" << std::endl;
}

LinalVector LinalVector::operator+(const LinalVector other)
{
    return LinalVector(this->dir_x + other.dir_x, this->dir_y + other.dir_y);
}

LinalVector LinalVector::operator*(const LinalVector other)
{
    return LinalVector(this->dir_x * other.dir_x, this->dir_y * other.dir_y);
}
