#include <iostream>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

using std::cout;
using std::endl;

const int screen_width = 640;
const int screen_height = 480;

int main()
{
    std::cout << "Hi" << std::endl;

    // Setup SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL init Error: " << SDL_GetError() << endl;
        return -1;
    }

    // Setup window (lots of magic numbers!)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    SDL_Window* window = SDL_CreateWindow(
        "ImGui SDL2+OpenGL example",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        screen_width, screen_height,
        SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN
    );
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    // Setup ImGui binding
    ImGui_ImplSdl_Init(window);

    // Background colour
    ImVec4 clear_color = (ImVec4)ImColor(114, 144, 154);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSdl_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        ImGui_ImplSdl_NewFrame(window);

        ImGui::Begin("DE SCHERM");
        ImGui::Text("HALLO IMGUI");
        ImGui::End();

        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
