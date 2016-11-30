//
// Created by mafn on 11/30/16.
//

#include <SDL2/SDL_opengl.h>
#include "SDLImguiApplication.hpp"
#include "imgui.h"
#include "imgui_impl_sdl.h"

using std::cout;
using std::endl;

SDLImguiApplication::SDLImguiApplication()
: _window(nullptr)
, _screen_width(640)
, _screen_height(480)
, _running(true)
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
        "Linear Algebra (Jorg&Thomas)",
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
    ImVec4 clear_color = (ImVec4)ImColor(114, 144, 154);
    ImVec4 line_color = (ImVec4)ImColor(255, 0, 0);

    this->_set_OpenGL_coordinate_mode();

    while (this->_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSdl_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                this->_running = false;
            }
        }

        // Imgui stuff
        ImGui_ImplSdl_NewFrame(this->_window);
        ImGui::Begin("DE SCHERM");
        ImGui::Text("HALLO IMGUI");
        ImGui::End();

        // Clear screen
        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a line
        glBegin(GL_LINES);
        glColor3d(line_color.x, line_color.y, line_color.z);
        glVertex2i(0, 0);
        glVertex2i(320, 240);
        glEnd();

        // Let ImGui render
        ImGui::Render();

        // Update screen
        SDL_GL_SwapWindow(this->_window);
    }
}

void SDLImguiApplication::_set_OpenGL_coordinate_mode()
{
    // Setup OpenGL for coordinate system drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->_screen_width, this->_screen_height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
