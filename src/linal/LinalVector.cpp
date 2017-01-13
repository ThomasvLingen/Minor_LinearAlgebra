//
// Created by mafn on 1/11/17.
//

#include "LinalVector.hpp"

LinalVector::LinalVector(double x, double y, double z, double w)
: LinalMatrix({
    {x},
    {y},
    {z},
    {w}
})
{

}

LinalVector::LinalVector(const LinalMatrix<double>& other)
: LinalMatrix(other.values)
{

}

LinalVector::LinalVector(const LinalMatrix<double>& matrix, size_t index)
: LinalVector(
    matrix.values[0][index],
    matrix.values[1][index],
    matrix.values[2][index]
)
{

}


double LinalVector::in_product(LinalVector& a, LinalVector& b)
{
    return a[x] * b[x] +
           a[y] * b[y] +
           a[z] * b[z];
}

LinalVector LinalVector::cross_product(LinalVector& a, LinalVector& b)
{
    return LinalVector {
        a[y] * b[z] - b[y] * a[z],
        b[x] * a[z] - a[x] * b[z],
        a[x] * b[y] - b[x] * a[y]
    };
}

double LinalVector::operator[](size_t index)
{
    return this->values[index][0];
}

LinalVector LinalVector::normalise()
{
    double length = this->length();

    return {
        (*this)[x] / length,
        (*this)[y] / length,
        (*this)[z] / length
    };
}

double LinalVector::length()
{
    return sqrt(
        (*this)[x] * (*this)[x]
        + (*this)[y] * (*this)[y]
        + (*this)[z] * (*this)[z]
    );
}
