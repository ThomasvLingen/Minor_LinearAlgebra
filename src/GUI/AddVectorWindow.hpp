//
// Created by mafn on 11/30/16.
//

#ifndef LINEARALGEBRA_ADDVECTORWINDOW_HPP
#define LINEARALGEBRA_ADDVECTORWINDOW_HPP

class SDLImguiApplication;

class AddVectorWindow {
public:
    AddVectorWindow(SDLImguiApplication& context);

    void GUI_logic();
private:
    SDLImguiApplication& _context;
};


#endif //LINEARALGEBRA_ADDVECTORWINDOW_HPP
