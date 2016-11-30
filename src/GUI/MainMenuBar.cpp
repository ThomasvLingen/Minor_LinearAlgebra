//
// Created by mafn on 11/30/16.
//

#include "MainMenuBar.hpp"
#include "imgui.h"
#include "../SDLImguiApplication.hpp"

MainMenuBar::MainMenuBar(SDLImguiApplication& context)
: add_vector_open(false)
, add_vector_sum_open(false)
, _context(context)
{

}

void MainMenuBar::GUI_logic()
{
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Add vector")) {
                add_vector_open = true;
            }
            if (ImGui::MenuItem("Sum of vectors")) {
                // We only want this to open if there are actually vectors to take a sum of
                if (this->_context._vectors.size() > 0) {
                    this->add_vector_sum_open = true;
                }
            }
            if (ImGui::MenuItem("Quit")) {
                this->_context._running = false;
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
