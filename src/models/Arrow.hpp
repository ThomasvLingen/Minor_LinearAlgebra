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
    const int _rotation_speed = 3;
    const int _movement_multiplier = 3;

    LinalMatrix<double> _translation_per_frame;

    LinalVector _direction;

    LinalMatrix<double> _get_translation_per_frame();
};


#endif //LINEARALGEBRA_ARROW_HPP
