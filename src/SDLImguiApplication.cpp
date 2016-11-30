//
// Created by mafn on 11/30/16.
//

#include <SDL2/SDL_opengl.h>
#include "SDLImguiApplication.hpp"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "linal/DrawableLinalVector.hpp"

#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

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
    ImVec4 clear_color = (ImVec4)ImColor(255, 255, 255);
    ImVec4 normal_line_color = (ImVec4)ImColor(255, 0, 0);
    ImVec4 sum_line_color = (ImVec4)ImColor(0, 255, 0);

    this->_set_OpenGL_coordinate_mode();

    bool add_vector_open = false;
    bool sum_of_vectors_open = false;

    vector<DrawableLinalVector> vectors;
    vector<DrawableLinalVector> sum_vectors;

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

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Add vector")) {
                    add_vector_open = true;
                }
                if (ImGui::MenuItem("Sum of vectors")) {
                    // We only want this to open if there are actually vectors to take a sum of
                    if (vectors.size() > 0) {
                        sum_of_vectors_open = true;
                    }
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        if (add_vector_open) {
            static int vector_dir_x = 0;
            static int vector_dir_y = 0;

            ImGui::Begin("Add vector screen", &add_vector_open);
            ImGui::Text("Vector params");
            ImGui::InputInt("x", &vector_dir_x, 10);
            ImGui::InputInt("y", &vector_dir_y, 10);

            if (ImGui::Button("Add")) {
                vectors.push_back(DrawableLinalVector(vector_dir_x, vector_dir_y));
            }

            ImGui::End();
        }

        if (sum_of_vectors_open) {
            // build vector list
            // TODO: This is ugly and stupid
            vector<string> names;
            for (int i = 0; i < vectors.size(); i++) {
                names.push_back(std::to_string(i));
            }
            vector<const char*> names_c_str;
            for (size_t i = 0; i < names.size(); ++i) {
                names_c_str.push_back(names[i].c_str());
            }

            static int from = 0;
            static int to = 0;

            ImGui::Begin("Sum of vectors", &sum_of_vectors_open);
            ImGui::ListBox("From", &from, names_c_str.data(), (int)names.size());
            ImGui::ListBox("To", &to, names_c_str.data(), (int)names.size());

            if (ImGui::Button("Add sum")) {
                sum_vectors.push_back(vectors[from] + vectors[to]);
            }

            ImGui::End();
        }

        // Clear screen
        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw vectors
        for (auto& v : vectors) {
            v.draw(normal_line_color);
        }

        for (auto& brommer : sum_vectors) {
            brommer.draw(sum_line_color);
        }

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
    glOrtho(-this->_screen_width/2, this->_screen_width/2,
            this->_screen_height/2, -this->_screen_height/2,
            -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
