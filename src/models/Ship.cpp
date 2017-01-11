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
    vector<LinalMatrix<double>> movement_stack;

    this->_roll_if_needed(keyboard, movement_stack);
    this->_move_if_needed(keyboard, movement_stack);

    // If movement_stack is empty, there is no movement to apply to the ship
    if (movement_stack.size() > 0) {
        // We calculate the resulting matrix of all the matrixes on the movement stack instead of applying them individually
        LinalMatrix<double> to_apply = LinalMatrix<double>::identity_matrix();

        for (LinalMatrix<double>& movement_matrix : movement_stack) {
            to_apply = movement_matrix * to_apply;
        }

        *this = to_apply * *this;
    }
}

///
/// \param direction direction of the roll, -1 is left, 1, is right. Internally, this is multiplied with the speed to
///                  get the final degrees to roll. So picking more than 1 or -1 will actually increase the roll speed.
LinalMatrix<double> Ship::_get_roll_matrix(int direction)
{
    return LinalMatrix::rotate_matrix(
        Axis::z,
        direction * this->_roll_speed,
        this->average_column()
    );
}

void Ship::_roll_if_needed(Keyboard& keyboard, vector<LinalMatrix<double>>& movement_stack)
{
    if (keyboard.is_down(SDLK_q) && keyboard.is_down(SDLK_e)) {
        // Do nothing, since Q and E cancel out each other
    }
    else if (keyboard.is_down(SDLK_q)) {
        movement_stack.push_back(this->_get_roll_matrix(this->_left_coeff));
    }
    else if (keyboard.is_down(SDLK_e)) {
        movement_stack.push_back(this->_get_roll_matrix(this->_right_coeff));
    }
}

LinalMatrix<double> Ship::_get_move_y_matrix(int direction)
{
    return LinalMatrix<double>::translation_matrix(0, this->_move_speed * (double)direction, 0);
}

LinalMatrix<double> Ship::_get_move_x_matrix(int direction)
{
    return LinalMatrix<double>::translation_matrix(this->_move_speed * (double)direction, 0, 0);;
}

void Ship::_move_if_needed(Keyboard& keyboard, MovementStack& movement_stack)
{
    if (keyboard.is_down(SDLK_w) && keyboard.is_down(SDLK_s)) {
        // Do nothing, since W and S cancel out each other
    }
    else if (keyboard.is_down(SDLK_w)) {
        movement_stack.push_back(this->_get_move_y_matrix(this->_move_up_coeff));
    }
    else if (keyboard.is_down(SDLK_s)) {
        movement_stack.push_back(this->_get_move_y_matrix(this->_move_down_coeff));
    }

    if (keyboard.is_down(SDLK_a) && keyboard.is_down(SDLK_d)) {
        // Do nothing, since A and D cancel out each other
    }
    else if (keyboard.is_down(SDLK_a)) {
        movement_stack.push_back(this->_get_move_x_matrix(this->_move_left_coeff));
    }
    else if (keyboard.is_down(SDLK_d)) {
        movement_stack.push_back(this->_get_move_x_matrix(this->_move_right_coeff));
    }
}
