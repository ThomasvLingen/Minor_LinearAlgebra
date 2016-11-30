//
// Created by mafn on 11/30/16.
//

#ifndef LINEARALGEBRA_SDLIMGUIAPPLICATION_HPP
#define LINEARALGEBRA_SDLIMGUIAPPLICATION_HPP


#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "imgui.h"

#include "linal/DrawableLinalVector.hpp"
#include "GUI/MainMenuBar.hpp"
#include "GUI/AddVectorWindow.hpp"
#include "GUI/AddVectorSumWindow.hpp"

class SDLImguiApplication {
friend class MainMenuBar;
friend class AddVectorWindow;
friend class AddVectorSumWindow;

public:
    SDLImguiApplication();

    void run();
private:
    SDL_Window* _window;
    SDL_GLContext _OpenGL_context;

    const int _screen_width;
    const int _screen_height;

    bool _running;

    // GUI elements
    MainMenuBar _main_menu;
    AddVectorWindow _add_vector_window;
    AddVectorSumWindow _add_vector_sum_window;

    std::vector<DrawableLinalVector> _vectors;
    std::vector<DrawableLinalVector> _sum_vectors;
    std::vector<DrawableLinalVector> _selected_vectors;

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
