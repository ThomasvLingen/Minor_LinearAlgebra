//
// Created by mafn on 11/30/16.
//

#include "AddVectorSumWindow.hpp"
#include "imgui.h"
#include "../SDLImguiApplication.hpp"

using std::string;
using std::vector;

AddVectorSumWindow::AddVectorSumWindow(SDLImguiApplication& context)
: _context(context)
{
}

void AddVectorSumWindow::GUI_logic()
{
    if (this->_context._main_menu.add_vector_sum_open) {
        // build vector list
        // TODO: This is ugly and stupid
        vector<string> names;
        for (int i = 0; i < this->_context._vectors.size(); i++) {
            names.push_back(std::to_string(i));
        }
        vector<const char*> names_c_str;
        for (size_t i = 0; i < names.size(); ++i) {
            names_c_str.push_back(names[i].c_str());
        }

        static int from = 0;
        static int to = 0;

        ImGui::Begin("Sum of vectors", &this->_context._main_menu.add_vector_sum_open);
        ImGui::ListBox("From", &from, names_c_str.data(), (int)names.size());
        ImGui::ListBox("To", &to, names_c_str.data(), (int)names.size());

//        if (ImGui::Button("Add sum")) {
//            this->_context._sum_vectors.push_back(this->_context._vectors[from] + this->_context._vectors[to]);
//        }

        this->_context._selected_vectors.clear();
        this->_context._selected_vectors.push_back(this->_context._vectors[from]);
        this->_context._selected_vectors.push_back(this->_context._vectors[to]);

        ImGui::End();
    }
}
