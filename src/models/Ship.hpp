//
// Created by mafn on 1/10/17.
//

#ifndef LINEARALGEBRA_SHIP_HPP
#define LINEARALGEBRA_SHIP_HPP


#include "../linal/LinalModel.hpp"
#include "../Keyboard.hpp"

typedef vector<LinalMatrix<double>> MovementStack;

class Ship : public LinalModel {
public:
    Ship();
    Ship(const LinalMatrix<double>& other);

    void handle_input(Keyboard& keyboard);
private:
    int _left_coeff = -1;
    int _right_coeff = 1;
    int _roll_speed = 3;
    double _move_speed = 3;
    int _move_left_coeff = 1;
    int _move_right_coeff = -1;
    int _move_up_coeff = 1;
    int _move_down_coeff = -1;

    void _roll_if_needed(Keyboard& keyboard, MovementStack& movement_stack);
    LinalMatrix<double> _get_roll_matrix(int direction);
    void _move_if_needed(Keyboard& keyboard, MovementStack& movement_stack);
    LinalMatrix<double> _get_move_y_matrix(int direction);
    LinalMatrix<double> _get_move_x_matrix(int direction);
};


#endif //LINEARALGEBRA_SHIP_HPP
