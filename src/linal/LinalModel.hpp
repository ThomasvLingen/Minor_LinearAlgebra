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
    virtual void draw(CameraMatrix& camera, PerspectiveMatrix& perspective);
private:

    static const size_t x = 0;
    static const size_t y = 1;
    static const size_t z = 2;
    static const size_t w = 3;

    LinalMatrix<double> get_screenspace_matrix(CameraMatrix& camera, PerspectiveMatrix& perspective);
    double _get_corrected_coord(double coordinate, double w, double axis_length);
};


#endif //LINEARALGEBRA_LINALMODEL_HPP
