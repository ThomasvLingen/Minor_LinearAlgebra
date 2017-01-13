//
// Created by mafn on 1/10/17.
//

#ifndef LINEARALGEBRA_SHIP_HPP
#define LINEARALGEBRA_SHIP_HPP


#include "../linal/LinalModel.hpp"
#include "../Keyboard.hpp"
#include "Arrow.hpp"

typedef vector<LinalMatrix<double>> MovementStack;

class Ship : public LinalModel {
public:
    Ship();
    Ship(const LinalMatrix<double>& other);

    void handle_input(Keyboard& keyboard);
    void update();
    void draw(CameraMatrix& camera, PerspectiveMatrix& perspective) override;

    LinalVector get_shoot_direction();
private:
    // Movement constants
    int _left_coeff = -1;
    int _right_coeff = 1;
    int _roll_speed = 3;
    double _move_speed = 3;
    int _move_left_coeff = 1;
    int _move_right_coeff = -1;
    int _move_up_coeff = 1;
    int _move_down_coeff = -1;
    int _move_forward_coeff = 1;
    int _move_backward_coeff = -1;
    double _growth_coeff = 0.01;
    double _shrink_coeff = -0.01;

    bool shot = false;
    vector<Arrow> arrows;
    void _shoot();

    void _do_movement(Keyboard& keyboard);
    void _roll_if_needed(Keyboard& keyboard, MovementStack& movement_stack);
    LinalMatrix<double> _get_roll_matrix(int direction);
    void _move_if_needed(Keyboard& keyboard, MovementStack& movement_stack);
    void _expand_if_needed(Keyboard& keyboard, MovementStack& movement_stack);
    LinalMatrix<double> _get_scaling_matrix(double growth_coeff);
    LinalMatrix<double> _get_move_x_matrix(int direction);
    LinalMatrix<double> _get_move_y_matrix(int direction);
    LinalMatrix<double> _get_move_z_matrix(int direction);

    LinalVector get_index_vector(size_t index);
};


#endif //LINEARALGEBRA_SHIP_HPP
