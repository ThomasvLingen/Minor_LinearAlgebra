//
// Created by mafn on 11/30/16.
//

#ifndef LINEARALGEBRA_ADDVECTORSUMWINDOW_HPP
#define LINEARALGEBRA_ADDVECTORSUMWINDOW_HPP

class SDLImguiApplication;

class AddVectorSumWindow {
public:
    AddVectorSumWindow(SDLImguiApplication& context);

    void GUI_logic();
private:
    SDLImguiApplication& _context;
};

#endif //LINEARALGEBRA_ADDVECTORSUMWINDOW_HPP
