//
// Created by mafn on 1/12/17.
//

#ifndef LINEARALGEBRA_ARROW_HPP
#define LINEARALGEBRA_ARROW_HPP


#include "../linal/LinalModel.hpp"

class Arrow {
public:
    Arrow(LinalVector direction, LinalMatrix<double> start_coordinates);

    LinalModel model;

    void update();
private:
    LinalVector _direction;
};


#endif //LINEARALGEBRA_ARROW_HPP
