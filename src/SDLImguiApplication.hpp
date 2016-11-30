//
// Created by mafn on 11/30/16.
//

#ifndef LINEARALGEBRA_SDLIMGUIAPPLICATION_HPP
#define LINEARALGEBRA_SDLIMGUIAPPLICATION_HPP


#include <SDL2/SDL.h>
#include <iostream>

class SDLImguiApplication {
public:
    SDLImguiApplication();

    void run();
private:
    SDL_Window* _window;
    SDL_GLContext _OpenGL_context;

    const int _screen_width;
    const int _screen_height;

    bool _running;

    void _set_OpenGL_coordinate_mode();
    bool _init_SDL();
    bool _init_OpenGL();
    bool _init_SDL_window();
    bool _init_imgui();
};


#endif //LINEARALGEBRA_SDLIMGUIAPPLICATION_HPP
