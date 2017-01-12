//
// Created by mafn on 1/12/17.
//

#ifndef LINEARALGEBRA_STATSWINDOW_HPP
#define LINEARALGEBRA_STATSWINDOW_HPP

class SDLImguiApplication;

class StatsWindow {
public:
    StatsWindow(SDLImguiApplication& context);

    void GUI_logic();
private:
    SDLImguiApplication& _context;
};


#endif //LINEARALGEBRA_STATSWINDOW_HPP
