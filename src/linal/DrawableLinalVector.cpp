//
// Created by mafn on 11/30/16.
//

#include <SDL2/SDL_opengl.h>
#include "DrawableLinalVector.hpp"

DrawableLinalVector::DrawableLinalVector(int dir_x, int dir_y)
: LinalVector(dir_x, dir_y)
{

}

void DrawableLinalVector::draw()
{
    glBegin(GL_LINES);
    glColor3d(255, 0, 0);
    glVertex2i(0, 0);
    glVertex2i(this->dir_x, this->dir_y);
    glEnd();
}
