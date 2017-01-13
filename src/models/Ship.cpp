//
// Created by mafn on 1/10/17.
//

#include "Ship.hpp"

Ship::Ship()
: model({
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

void Ship::handle_input(Keyboard& keyboard, vector<Arrow>& arrows)
{
    if (!this->_shot) {
        if (keyboard.is_down(SDLK_SPACE)) {
            this->_shoot(arrows);

            this->_shot = true;
        }
    }

    this->_do_movement(keyboard);
}


void Ship::_do_movement(Keyboard& keyboard)
{
    vector<LinalMatrix<double>> movement_stack;

    this->_roll_if_needed(keyboard, movement_stack);
    this->_move_if_needed(keyboard, movement_stack);
    this->_expand_if_needed(keyboard, movement_stack);

    // If movement_stack is empty, there is no movement to apply to the ship
    if (movement_stack.size() > 0) {
        // We calculate the resulting matrix of all the matrixes on the movement stack instead of applying them individually
        LinalMatrix<double> to_apply = LinalMatrix<double>::identity_matrix();

        for (LinalMatrix<double>& movement_matrix : movement_stack) {
            to_apply = movement_matrix * to_apply;
        }

        this->model = to_apply * this->model;
    }
}

///
/// \param direction direction of the roll, -1 is left, 1, is right. Internally, this is multiplied with the speed to
///                  get the final degrees to roll. So picking more than 1 or -1 will actually increase the roll speed.
LinalMatrix<double> Ship::_get_roll_matrix(int direction)
{
    return LinalMatrix<double>::rotate_matrix(
        Axis::z,
        direction * this->_roll_speed,
        this->model.average_column()
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

    if (keyboard.is_down(SDLK_z) && keyboard.is_down(SDLK_x)) {
        // Do nothing, since A and D cancel out each other
    }
    else if (keyboard.is_down(SDLK_z)) {
        movement_stack.push_back(this->_get_move_z_matrix(this->_move_forward_coeff));
    }
    else if (keyboard.is_down(SDLK_x)) {
        movement_stack.push_back(this->_get_move_z_matrix(this->_move_backward_coeff));
    }
}

void Ship::_expand_if_needed(Keyboard& keyboard, MovementStack& movement_stack)
{
    if (keyboard.is_down(SDLK_EQUALS) && keyboard.is_down(SDLK_MINUS)) {
        // Do nothing, since + and - cancel each other out
    }
    else if (keyboard.is_down(SDLK_EQUALS)) {
        movement_stack.push_back(this->_get_scaling_matrix(this->_growth_coeff));
    }
    else if (keyboard.is_down(SDLK_MINUS)) {
        movement_stack.push_back(this->_get_scaling_matrix(this->_shrink_coeff));
    }
}

LinalMatrix<double> Ship::_get_scaling_matrix(double coeff)
{
    return LinalMatrix<double>::scaling_matrix(1 + coeff, 1 + coeff, 1 + coeff);
}

LinalMatrix<double> Ship::_get_move_x_matrix(int direction)
{
    return LinalMatrix<double>::translation_matrix(this->_move_speed * (double)direction, 0, 0);;
}

LinalMatrix<double> Ship::_get_move_y_matrix(int direction)
{
    return LinalMatrix<double>::translation_matrix(0, this->_move_speed * (double)direction, 0);
}

LinalMatrix<double> Ship::_get_move_z_matrix(int direction)
{
    return LinalMatrix<double>::translation_matrix(0, 0, this->_move_speed * (double)direction);
}

LinalVector Ship::_get_index_vector(size_t index)
{
    return LinalVector(this->model, index);
}

LinalVector Ship::get_shoot_direction()
{
    // Shoot direction indexes
    const size_t base_index = 10;
    const size_t plane_1_index = 16;
    const size_t plane_2_index = 8;

    LinalVector a = this->_get_index_vector(plane_1_index) - this->_get_index_vector(base_index);
    LinalVector b = this->_get_index_vector(plane_2_index) - this->_get_index_vector(base_index);

    // Get cross product to get a vector perpendicular to the top plane of the ship.
    return LinalVector::cross_product(a, b).normalise();
}

void Ship::_shoot(vector<Arrow>& arrows)
{
    arrows.push_back(Arrow(this->get_shoot_direction(), this->model.average_column()));
}
