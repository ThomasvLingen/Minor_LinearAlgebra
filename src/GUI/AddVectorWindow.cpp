//
// Created by mafn on 11/30/16.
//

#include "AddVectorWindow.hpp"
#include "imgui.h"
#include "../linal/DrawableLinalVector.hpp"
#include "../SDLImguiApplication.hpp"


AddVectorWindow::AddVectorWindow(SDLImguiApplication& context)
: _context(context)
{
}

void AddVectorWindow::GUI_logic()
{
    if (this->_context._main_menu.add_vector_open) {
        static int vector_dir_x = 0;
        static int vector_dir_y = 0;

        ImGui::Begin("Add vector screen", &this->_context._main_menu.add_vector_open);
        ImGui::Text("Vector params");
        ImGui::InputInt("x", &vector_dir_x, 10);
        ImGui::InputInt("y", &vector_dir_y, 10);

        if (ImGui::Button("Add")) {
            this->_context._vectors.push_back(DrawableLinalVector(vector_dir_x, vector_dir_y));
        }

        ImGui::End();
    }
}
