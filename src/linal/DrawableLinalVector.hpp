//
// Created by mafn on 11/30/16.
//

#ifndef LINEARALGEBRA_DRAWABLELINALVECTOR_HPP
#define LINEARALGEBRA_DRAWABLELINALVECTOR_HPP


#include "LinalVector.hpp"

class DrawableLinalVector : public LinalVector {
public:
    DrawableLinalVector(int dir_x, int dir_y);
    void draw();
private:
};


#endif //LINEARALGEBRA_DRAWABLELINALVECTOR_HPP
