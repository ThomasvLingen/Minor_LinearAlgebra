#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <map>

class Keyboard {
    // Stores pressed keys
    std::map<SDL_Keycode, bool> keys;

  public:
    void key_pressed(SDL_Keycode);
    void key_released(SDL_Keycode);
    bool is_down(SDL_Keycode);
};
