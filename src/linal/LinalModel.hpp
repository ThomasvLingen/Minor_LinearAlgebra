//
// Created by mafn on 1/10/17.
//

#ifndef LINEARALGEBRA_LINALMODEL_HPP
#define LINEARALGEBRA_LINALMODEL_HPP


#include "LinalMatrix.hpp"

class LinalModel : public LinalMatrix<double> {
public:
    LinalModel(vector<vector<double>> vertices);
    void draw();
private:
};


#endif //LINEARALGEBRA_LINALMODEL_HPP
