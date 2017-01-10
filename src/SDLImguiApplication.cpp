//
// Created by mafn on 11/30/16.
//

#include <SDL2/SDL_opengl.h>
#include "SDLImguiApplication.hpp"
#include "imgui_impl_sdl.h"
#include <GL/glu.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

SDLImguiApplication::SDLImguiApplication()
: _window(nullptr)
, _screen_width(640)
, _screen_height(480)
, _running(true)
, _main_menu(*this)
, _add_vector_window(*this)
, _add_vector_sum_window(*this)
{
    if (!this->_init_SDL()) {
        cout << "Could not init SDL" << endl;
    }

    if (!this->_init_SDL_window()) {
        cout << "Could not init SDL OpenGL window" << endl;
    }

    if (!this->_init_OpenGL()) {
        cout << "Could not init OpenGL" << endl;
    }

    if (!this->_init_imgui()) {
        cout << "Could not init ImGui" << endl;
    }
}

bool SDLImguiApplication::_init_SDL()
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL init Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

bool SDLImguiApplication::_init_OpenGL()
{
    // Step one, set GL attributes
    int returns = 0;

    returns += SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    returns += SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    returns += SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    returns += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    returns += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    if (returns != 0) {
        cout << "Something went wrong while setting OpenGL attributes through SDL: " << SDL_GetError() << endl;
        return false;
    }

    // Step two, create the OpenGL context
    this->_OpenGL_context = SDL_GL_CreateContext(this->_window);

    if (this->_OpenGL_context == NULL) {
        cout << "Something went wrong while creating the OpenGL context through SDL: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

bool SDLImguiApplication::_init_SDL_window()
{
    SDL_Window* window = SDL_CreateWindow(
        "Linear Algebra (Jorg & Thomas)",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        this->_screen_width, this->_screen_height,
        SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        cout << "Could not create SDL OpenGL Window: " << SDL_GetError() << endl;
        return false;
    }

    this->_window = window;
    return true;
}

bool SDLImguiApplication::_init_imgui()
{
    ImGui_ImplSdl_Init(this->_window);

    return true;
}

void SDLImguiApplication::run()
{
    ImVec4 normal_line_color = (ImVec4)ImColor(255, 0, 0);
    ImVec4 sum_line_color = (ImVec4)ImColor(0, 0, 255);
    ImVec4 selected_line_color = (ImVec4)ImColor(0, 255, 0);

    this->_set_OpenGL_coordinate_mode();

    while (this->_running) {
        this->_handle_SDL_events();

        this->_GUI_logic();

        this->_clear_screen();

        // Draw vectors
        for (auto& v : this->_vectors) {
            v.draw(normal_line_color);
        }

        for (auto& brommer : this->_sum_vectors) {
            brommer.draw(sum_line_color);
        }

        for (auto& v : this->_selected_vectors) {
            v.draw(selected_line_color);
        }

        /* test 3d object */
        glMatrixMode(GL_MODELVIEW);
        glBegin(GL_QUADS);        // Draw The Cube Using quads
        glLoadIdentity();
        glColor3f(0.0f,1.0f,0.0f);    // Color Blue
        glVertex3i( 50, 50,-50);    // Top Right Of The Quad (Top)
        glVertex3i(-50, 50,-50);    // Top Left Of The Quad (Top)
        glVertex3i(-50, 50, 50);    // Bottom Left Of The Quad (Top)
        glVertex3i( 50, 50, 50);    // Bottom Right Of The Quad (Top)
        glColor3f(1.0f,0.5f,0.0f);    // Color Orange
        glVertex3i( 50,-50, 50);    // Top Right Of The Quad (Bottom)
        glVertex3i(-50,-50, 50);    // Top Left Of The Quad (Bottom)
        glVertex3i(-50,-50,-50);    // Bottom Left Of The Quad (Bottom)
        glVertex3i( 50,-50,-50);    // Bottom Right Of The Quad (Bottom)
        glColor3f(1.0f,0.0f,0.0f);    // Color Red
        glVertex3i( 50, 50, 50);    // Top Right Of The Quad (Front)
        glVertex3i(-50, 50, 50);    // Top Left Of The Quad (Front)
        glVertex3i(-50,-50, 50);    // Bottom Left Of The Quad (Front)
        glVertex3i( 50,-50, 50);    // Bottom Right Of The Quad (Front)
        glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
        glVertex3i( 50,-50,-50);    // Top Right Of The Quad (Back)
        glVertex3i(-50,-50,-50);    // Top Left Of The Quad (Back)
        glVertex3i(-50, 50,-50);    // Bottom Left Of The Quad (Back)
        glVertex3i( 50, 50,-50);    // Bottom Right Of The Quad (Back)
        glColor3f(0.0f,0.0f,1.0f);    // Color Blue
        glVertex3i(-50, 50, 50);    // Top Right Of The Quad (Left)
        glVertex3i(-50, 50,-50);    // Top Left Of The Quad (Left)
        glVertex3i(-50,-50,-50);    // Bottom Left Of The Quad (Left)
        glVertex3i(-50,-50, 50);    // Bottom Right Of The Quad (Left)
        glColor3f(1.0f,0.0f,1.0f);    // Color Violet
        glVertex3i( 50, 50,-50);    // Top Right Of The Quad (Right)
        glVertex3i( 50, 50, 50);    // Top Left Of The Quad (Right)
        glVertex3i( 50,-50, 50);    // Bottom Left Of The Quad (Right)
        glVertex3i( 50,-50,-50);    // Bottom Right Of The Quad (Right)
        glEnd();            // End Drawing The Cube
        glRotatef(1,1.0,0.0,0.0);
        glRotatef(2,0.0,1.0,0.0);
        glRotatef(3,0.0,0.0,1.0);
        glFlush();

        // Let ImGui render
        ImGui::Render();

        // Update screen
        SDL_GL_SwapWindow(this->_window);
    }
}

void SDLImguiApplication::_set_OpenGL_coordinate_mode()
{
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);



    // Setup OpenGL for coordinate system drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-this->_screen_width/2, this->_screen_width/2,
            -this->_screen_height/2, this->_screen_height/2,
            -100, 100);
    glMatrixMode(GL_MODELVIEW);
}

void SDLImguiApplication::_handle_SDL_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSdl_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            this->_running = false;
        }
    }
}

void SDLImguiApplication::_clear_screen()
{
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    // glClear(GL_COLOR_BUFFER_BIT);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SDLImguiApplication::_GUI_logic()
{
    // Imgui stuff
    ImGui_ImplSdl_NewFrame(this->_window);

    this->_main_menu.GUI_logic();
    this->_add_vector_window.GUI_logic();
    this->_add_vector_sum_window.GUI_logic();
}
