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
}

void Arrow::update()
{
    LinalMatrix<double> movement = LinalMatrix<double>::translation_matrix(
        this->_direction[0],
        this->_direction[1],
        this->_direction[2]
    );
    LinalMatrix<double> rotation = LinalMatrix<double>::rotate_matrix(Axis::z, 1, this->model.average_column());
    LinalMatrix<double> transformation = movement * rotation;

    this->model = transformation * this->model;
}
