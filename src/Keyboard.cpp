#include "Keyboard.hpp"

void Keyboard::key_pressed(SDL_Keycode pressed) {
    keys[pressed] = true;
}

void Keyboard::key_released(SDL_Keycode released) {
    keys[released] = false;
}

bool Keyboard::is_down(SDL_Keycode query) {
    return keys[query];
}
