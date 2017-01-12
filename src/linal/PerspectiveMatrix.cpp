//
// Created by mafn on 1/12/17.
//

#include "PerspectiveMatrix.hpp"

PerspectiveMatrix::PerspectiveMatrix(double near, double far, int vertical_fov, double aspect_ratio)
{
    this->_matrix = this->_calc_perspective_matrix(near, far, vertical_fov, aspect_ratio);
}

LinalMatrix<double> PerspectiveMatrix::get_matrix()
{
    return this->_matrix;
}

LinalMatrix<double> PerspectiveMatrix::_calc_perspective_matrix(double near, double far, int vertical_fov, double aspect_ratio)
{
    double scale = near * tan(0.5 * DegreeUtil::degree_to_radian(vertical_fov));

    double z_calc = -far / (far - near);
    double w_calc = (-far * near) / (far - near);

    return LinalMatrix<double>({
        {scale, 0, 0, 0},
        {0, scale, 0, 0},
        {0, 0, z_calc, -1},
        {0, 0, w_calc, 0}
    });
}
