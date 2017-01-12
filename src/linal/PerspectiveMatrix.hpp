//
// Created by mafn on 1/12/17.
//

#ifndef LINEARALGEBRA_PERSPECTIVEMATRIX_HPP
#define LINEARALGEBRA_PERSPECTIVEMATRIX_HPP


#include "LinalMatrix.hpp"

class PerspectiveMatrix {
public:
    PerspectiveMatrix(double near, double far, int vertical_fov, double aspect_ratio = 1.0);

    LinalMatrix<double> get_matrix();
private:
    static const size_t x = 0;
    static const size_t y = 1;
    static const size_t z = 2;

    LinalMatrix<double> _matrix;
    LinalMatrix<double> _calc_perspective_matrix(double near, double far, int vertical_fov, double aspect_ratio);
};


#endif //LINEARALGEBRA_PERSPECTIVEMATRIX_HPP
