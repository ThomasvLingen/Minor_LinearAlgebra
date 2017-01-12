//
// Created by mafn on 1/10/17.
//

#ifndef LINEARALGEBRA_LINALMODEL_HPP
#define LINEARALGEBRA_LINALMODEL_HPP


#include "LinalMatrix.hpp"
#include "CameraMatrix.hpp"
#include "PerspectiveMatrix.hpp"

class LinalModel : public LinalMatrix<double> {
public:
    LinalModel(vector<vector<double>> vertices);
    LinalModel(const LinalMatrix<double>& other);
    void draw(CameraMatrix& camera, PerspectiveMatrix& perspective);
private:

    LinalMatrix<double> get_screenspace_matrix(CameraMatrix& camera, PerspectiveMatrix& perspective);
    LinalMatrix<double> get_correction_matrix(int screen_size);
};


#endif //LINEARALGEBRA_LINALMODEL_HPP
