//
// Created by mafn on 1/11/17.
//

#include "LinalVector.hpp"

LinalVector::LinalVector(double x, double y, double z)
: LinalMatrix({
    {x},
    {y},
    {z}
})
{

}

LinalVector::LinalVector(const LinalMatrix& other)
: LinalMatrix(other.values)
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
    double length = sqrt(
          (*this)[x] * (*this)[x]
        + (*this)[y] * (*this)[y]
        + (*this)[z] * (*this)[z]
    );

    return {
        (*this)[x] / length,
        (*this)[y] / length,
        (*this)[z] / length
    };
}


