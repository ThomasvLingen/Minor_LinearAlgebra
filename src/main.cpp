#include <iostream>
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <GL/gl3w.h>
#include <SDL2/SDL.h>

using std::cout;
using std::endl;

int main()
{
    std::cout << "Hi" << std::endl;

    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        cout << "Error: " << SDL_GetError() << endl;
        return -1;
    }

    // Setup window (whole lot of magic settings)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    SDL_Window *window = SDL_CreateWindow("ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    gl3wInit();

    // Setup ImGui binding
    ImGui_ImplSdlGL3_Init(window);
    // Some color that IMGUI uses
    ImVec4 clear_color = ImColor(114, 144, 154);

    bool running = true;
    while (running) {
        // Handle SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSdlGL3_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        ImGui_ImplSdlGL3_NewFrame(window);

        // ImGui::Begin("FUCK");
        ImGui::Text("HALLO FAGGOT");
        // ImGui::End();

        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
