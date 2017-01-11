//
// Created by mafn on 1/10/17.
//

#include "Ship.hpp"

Ship::Ship()
: LinalModel({
    // For reference, see big boy paper
    //             side 1                |                side 2                 |              side 3
    // 1    | 2      | 3       | 4       | 5       | 6       | 7       | 8       | 9       | 10      | 11      | 12
    {-50, 50, 50, 50 , 50 , -50, -50, -50, -50, 0  , 0  , 0  , 0  , -50, -50, -50, 50 , 0  , 0  , 0  , 0  , 50 , 50 , 50},
    {20 , 20, 20, -20, -20, -20, -20, 20 , 20 , 20 , 20 , -20, -20, -20, -20,  20, 20 , 20 , 20 , -20, -20, -20, -20, 20},
    {0  , 0 , 0 , 0  , 0  , 0  , 0  , 0  , 0  , 100, 100, 100, 100, 0  , 0  , 0  , 0  , 100, 100, 100, 100, 0  , 0  , 0 },
    {1  , 1 , 1 , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1 }
 })
{

}

Ship::Ship(const LinalMatrix<double>& other)
: LinalModel(other.values)
{

}

void Ship::handle_input(Keyboard& keyboard)
{
    this->_roll_if_needed(keyboard);
    this->_move_if_needed(keyboard);
}

///
/// \param direction direction of the roll, -1 is left, 1, is right. Internally, this is multiplied with the speed to
///                  get the final degrees to roll. So picking more than 1 or -1 will actually increase the roll speed.
void Ship::_roll(int direction)
{
    LinalMatrix<double> rotation_matrix = LinalMatrix::rotate_matrix(
        Axis::z,
        direction * this->_roll_speed,
        this->average_column()
    );

    *this = rotation_matrix * *this;
}

void Ship::_roll_if_needed(Keyboard& keyboard)
{
    if (keyboard.is_down(SDLK_q) && keyboard.is_down(SDLK_e)) {
        // Do nothing, since Q and E cancel out each other
    }
    else if (keyboard.is_down(SDLK_q)) {
        this->_roll(this->_left_coeff);
    }
    else if (keyboard.is_down(SDLK_e)) {
        this->_roll(this->_right_coeff);
    }
}

void Ship::_move_x(int direction)
{
    LinalMatrix<double> translation = LinalMatrix<double>::translation_matrix(this->_move_speed * (double)direction, 0, 0);

    *this = translation * *this;
}

void Ship::_move_y(int direction)
{
    LinalMatrix<double> translation = LinalMatrix<double>::translation_matrix(0, this->_move_speed * (double)direction, 0);

    *this = translation * *this;
}

void Ship::_move_if_needed(Keyboard& keyboard)
{
    if (keyboard.is_down(SDLK_w) && keyboard.is_down(SDLK_s)) {
        // Do nothing, since W and S cancel out each other
    }
    else if (keyboard.is_down(SDLK_w)) {
        this->_move_y(this->_move_up_coeff);
    }
    else if (keyboard.is_down(SDLK_s)) {
        this->_move_y(this->_move_down_coeff);
    }

    if (keyboard.is_down(SDLK_a) && keyboard.is_down(SDLK_d)) {
        // Do nothing, since A and D cancel out each other
    }
    else if (keyboard.is_down(SDLK_a)) {
        this->_move_x(this->_move_left_coeff);
    }
    else if (keyboard.is_down(SDLK_d)) {
        this->_move_x(this->_move_right_coeff);
    }
}
