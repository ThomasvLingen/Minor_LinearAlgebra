//
// Created by mafn on 11/30/16.
//

#ifndef LINEARALGEBRA_MAINMENUBAR_HPP
#define LINEARALGEBRA_MAINMENUBAR_HPP


class SDLImguiApplication;

class MainMenuBar {

public:
    MainMenuBar(SDLImguiApplication& context);

    bool add_vector_open;
    bool add_vector_sum_open;

    void GUI_logic();
private:
    SDLImguiApplication& _context;
};


#endif //LINEARALGEBRA_MAINMENUBAR_HPP
