//
// Created by mafn on 1/10/17.
//

#include "LinalModel.hpp"

#include <cassert>
#include <SDL2/SDL_opengl.h>


LinalModel::LinalModel(vector<vector<double>> vertices)
: LinalMatrix(vertices)
{
    // 4 rows (x, y, z, w)
    assert(vertices.size() == 4);
    // More than 1 vert to draw
    assert(vertices[0].size() > 0);
}

void LinalModel::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_LINES); // The model is drawn using lines
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    // We unfortunately can't range based for here
    for (size_t vert_index = 0; vert_index < this->x_size; vert_index++) {
        glVertex3d(this->values[0][vert_index], this->values[1][vert_index], this->values[2][vert_index]);
    }
    glEnd();
}
