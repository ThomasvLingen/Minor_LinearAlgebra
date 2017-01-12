//
// Created by mafn on 1/12/17.
//

#include "CameraMatrix.hpp"

CameraMatrix::CameraMatrix(LinalVector eye, LinalVector look_at, LinalVector up)
{
    this->_matrix = this->_calc_camera_matrix(eye, look_at, up);
}

LinalMatrix<double> CameraMatrix::_calc_camera_matrix(LinalVector eye, LinalVector look_at, LinalVector up)
{
    LinalVector z_vec = LinalVector(eye - look_at).normalise();
    LinalVector y_vec = up.normalise();
    LinalVector x_vec = LinalVector::cross_product(y_vec, z_vec).normalise();
    y_vec = LinalVector::cross_product(z_vec, x_vec).normalise();

    return LinalMatrix<double>({
        {x_vec[x], x_vec[y], x_vec[z], -LinalVector::in_product(x_vec, eye)},
        {y_vec[x], y_vec[y], y_vec[z], -LinalVector::in_product(y_vec, eye)},
        {z_vec[x], z_vec[y], z_vec[z], -LinalVector::in_product(z_vec, eye)},
        {0       , 0       , 0       , 1}
    });
}

LinalMatrix<double> CameraMatrix::get_matrix()
{
    return this->_matrix;
}
