//
// Created by mafn on 1/11/17.
//

#ifndef LINEARALGEBRA_LINALVECTOR_HPP
#define LINEARALGEBRA_LINALVECTOR_HPP


#include "LinalMatrix.hpp"

class LinalVector : public LinalMatrix<double> {
public:
    LinalVector(double x, double y, double z, double w = 1);
    LinalVector(const LinalMatrix<double>& other);
    LinalVector(const LinalMatrix<double>& matrix, size_t index);

    LinalVector normalise();
    double length();
    double operator[](size_t index);

    static double in_product(LinalVector& a, LinalVector& b);
    static LinalVector cross_product(LinalVector& a, LinalVector& b);
private:
    static const size_t x = 0;
    static const size_t y = 1;
    static const size_t z = 2;

};


#endif //LINEARALGEBRA_LINALVECTOR_HPP
