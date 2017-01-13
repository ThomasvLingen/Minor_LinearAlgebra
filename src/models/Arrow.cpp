//
// Created by mafn on 1/12/17.
//

#include "Arrow.hpp"

Arrow::Arrow(LinalVector direction, LinalMatrix<double> start_coordinates)
: model({
    // This is a simple square
    {-20, 20 , -20, -20, 20, -20, 20, 20 },
    {-20, -20, -20, 20 , 20, 20 , 20, -20},
    {0  , 0  , 0  , 0  , 0 , 0  , 0 , 0  },
    {1  , 1  , 1  , 1  , 1 , 1  , 1 , 1  }
})
, _direction(direction)
{
    LinalMatrix<double> movement_to_start = LinalMatrix<double>::translation_matrix(
        start_coordinates.values[0][0],
        start_coordinates.values[1][0],
        start_coordinates.values[2][0]
    );

    this->model = movement_to_start * this->model;
    this->_translation_per_frame = this->_get_translation_per_frame();
}

void Arrow::update()
{
    LinalMatrix<double> rot_z = LinalMatrix<double>::rotate_matrix(Axis::z, this->_rotation_speed, this->model.average_column());
    LinalMatrix<double> rot_y = LinalMatrix<double>::rotate_matrix(Axis::y, this->_rotation_speed, this->model.average_column());
    LinalMatrix<double> rot_x = LinalMatrix<double>::rotate_matrix(Axis::x, this->_rotation_speed, this->model.average_column());
    LinalMatrix<double> transformation = this->_translation_per_frame * rot_x * rot_y * rot_z;

    this->model = transformation * this->model;
}

LinalMatrix<double> Arrow::_get_translation_per_frame()
{
    return LinalMatrix<double>::translation_matrix(
        this->_direction[0] * this->_movement_multiplier,
        this->_direction[1] * this->_movement_multiplier,
        this->_direction[2] * this->_movement_multiplier
    );
}
