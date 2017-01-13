//
// Created by mafn on 11/30/16.
//

#ifndef LINEARALGEBRA_SDLIMGUIAPPLICATION_HPP
#define LINEARALGEBRA_SDLIMGUIAPPLICATION_HPP


#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "imgui.h"

#include "GUI/MainMenuBar.hpp"
#include "linal/LinalModel.hpp"
#include "models/Ship.hpp"
#include "Keyboard.hpp"
#include "GUI/StatsWindow.hpp"

class SDLImguiApplication {
friend class MainMenuBar;
friend class StatsWindow;

public:
    SDLImguiApplication();

    void run();
private:
    SDL_Window* _window;
    SDL_GLContext _OpenGL_context;

    const int _screen_width;
    const int _screen_height;

    bool _running;

    // Test model thing
    Ship ship;
    vector<Arrow> arrows;

    // GUI elements
    MainMenuBar _main_menu;
    StatsWindow _stats;
    Keyboard keyboard;

    // Perspective constants
    const int vertical_fov = 90;
    const double z_near = 1;
    const double z_far = 1000;

    LinalMatrix<double> eye = vector<vector<double>> {
        {0},
        {0},
        {-1000},
    };

    // This is the center
    LinalMatrix<double> look_at = vector<vector<double>> {
        {0},
        {0},
        {0},
    };

    LinalMatrix<double> up = vector<vector<double>> {
        {0},
        {1},
        {0},
    };

    CameraMatrix _camera;
    PerspectiveMatrix _perspective;

    void _handle_SDL_events();
    void _GUI_logic();
    ImVec4 clear_color = (ImVec4)ImColor(255, 255, 255);
    void _clear_screen();

    void _set_OpenGL_coordinate_mode();
    bool _init_SDL();
    bool _init_OpenGL();
    bool _init_SDL_window();
    bool _init_imgui();
};


#endif //LINEARALGEBRA_SDLIMGUIAPPLICATION_HPP
