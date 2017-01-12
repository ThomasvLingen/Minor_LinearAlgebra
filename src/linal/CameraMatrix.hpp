//
// Created by mafn on 1/12/17.
//

#ifndef LINEARALGEBRA_CAMERAMATRIX_HPP
#define LINEARALGEBRA_CAMERAMATRIX_HPP


#include "LinalMatrix.hpp"
#include "LinalVector.hpp"

class CameraMatrix {
public:
    CameraMatrix(LinalVector eye, LinalVector look_at, LinalVector up);

    LinalMatrix<double> get_matrix();
private:
    static const size_t x = 0;
    static const size_t y = 1;
    static const size_t z = 2;

    LinalMatrix<double> _matrix;

    LinalMatrix<double> _calc_camera_matrix(LinalVector eye, LinalVector look_at, LinalVector up);
};


#endif //LINEARALGEBRA_CAMERAMATRIX_HPP
