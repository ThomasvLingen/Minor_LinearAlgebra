//
// Created by mafn on 11/30/16.
//

#ifndef LINEARALGEBRA_LINALVECTOR_HPP
#define LINEARALGEBRA_LINALVECTOR_HPP


class LinalVector {
public:
    LinalVector(int x, int y);

    int dir_x;
    int dir_y;

    void multiply_by_factor(int factor);
    void print();

    LinalVector operator+(const LinalVector other);
    LinalVector operator*(const LinalVector other);
};


#endif //LINEARALGEBRA_LINALVECTOR_HPP
