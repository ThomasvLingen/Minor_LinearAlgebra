//
// Created by mafn on 1/10/17.
//

#ifndef LINEARALGEBRA_SHIP_HPP
#define LINEARALGEBRA_SHIP_HPP


#include "../linal/LinalModel.hpp"

class Ship : public LinalModel {
public:
    Ship();
    Ship(const LinalMatrix<double>& other);
private:
};


#endif //LINEARALGEBRA_SHIP_HPP
