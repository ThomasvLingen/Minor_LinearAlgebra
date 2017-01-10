//
// Created by mafn on 11/30/16.
//

#ifndef LINEARALGEBRA_LINALVECTOR_HPP
#define LINEARALGEBRA_LINALVECTOR_HPP

#include "LinalMatrix.hpp"

class LinalVector : public LinalMatrix<int> {
public:
    LinalVector(int x, int y);
    LinalVector(LinalMatrix obj);

//    void multiply_by_factor(int factor);

//    LinalVector operator+(const LinalVector other);
//    LinalVector operator*(const LinalVector other);
};


#endif //LINEARALGEBRA_LINALVECTOR_HPP
