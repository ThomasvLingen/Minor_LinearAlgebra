//
// Created by mafn on 11/30/16.
//

#include "MainMenuBar.hpp"
#include "imgui.h"
#include "../SDLImguiApplication.hpp"

MainMenuBar::MainMenuBar(SDLImguiApplication& context)
: add_vector_open(false)
, add_vector_sum_open(false)
, stats_window_open(false)
, _context(context)
{

}

void MainMenuBar::GUI_logic()
{
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Stats window")) {
                this->stats_window_open = true;
            }
            if (ImGui::MenuItem("Quit")) {
                this->_context._running = false;
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
