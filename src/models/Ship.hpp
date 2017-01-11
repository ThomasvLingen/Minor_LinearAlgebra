//
// Created by mafn on 1/10/17.
//

#ifndef LINEARALGEBRA_SHIP_HPP
#define LINEARALGEBRA_SHIP_HPP


#include "../linal/LinalModel.hpp"
#include "../Keyboard.hpp"

class Ship : public LinalModel {
public:
    Ship();
    Ship(const LinalMatrix<double>& other);

    void handle_input(Keyboard& keyboard);
private:
    int _left_coeff = -1;
    int _right_coeff = 1;
    int _roll_speed = 3;

    void _roll_if_needed(Keyboard& keyboard);
    void _roll(int direction);
};


#endif //LINEARALGEBRA_SHIP_HPP
