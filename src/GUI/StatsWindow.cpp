//
// Created by mafn on 1/12/17.
//

#include "StatsWindow.hpp"

#include "../SDLImguiApplication.hpp"

StatsWindow::StatsWindow(SDLImguiApplication& context)
: _context(context)
{

}

void StatsWindow::GUI_logic()
{
    if (this->_context._main_menu.stats_window_open) {
        ImGui::Begin("Stats", &this->_context._main_menu.stats_window_open);

        LinalMatrix<double> ship_coords = this->_context.ship.model.average_column();

        ImGui::Text("Ship coordinates");
        ImGui::Text("x: %f", ship_coords.values[0][0]);
        ImGui::Text("y: %f", ship_coords.values[1][0]);
        ImGui::Text("z: %f", ship_coords.values[2][0]);

        ImGui::End();
    }
}
