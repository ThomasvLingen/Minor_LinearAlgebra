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

LinalModel::LinalModel(const LinalMatrix<double>& other)
: LinalMatrix(other)
{

}

void LinalModel::draw(CameraMatrix& camera, PerspectiveMatrix& perspective)
{
    LinalModel draw_vertices = this->get_screenspace_matrix(camera, perspective);

    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_LINES); // The model is drawn using lines
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    // We unfortunately can't range based for here
    for (size_t vert_index = 0; vert_index < draw_vertices.x_size; vert_index++) {
        if (draw_vertices.values[3][vert_index] > 0) {
            glVertex3d(
                320 +
                (((draw_vertices.values[0][vert_index] + 1) / (draw_vertices.values[3][vert_index] + 0.00000001)) *
                 320),
                320 +
                (((draw_vertices.values[1][vert_index] + 1) / (draw_vertices.values[3][vert_index] + 0.00000001)) *
                 320),
                500 +
                (((draw_vertices.values[2][vert_index] + 1) / (draw_vertices.values[3][vert_index] + 0.00000001)) *
                 500)
            );
        }
    }
    glEnd();
}

LinalMatrix<double> LinalModel::get_screenspace_matrix(CameraMatrix& camera, PerspectiveMatrix& perspective)
{
    LinalMatrix<double> screenspace = perspective.get_matrix() * camera.get_matrix();
    return screenspace * *this;
}

LinalMatrix<double> LinalModel::get_correction_matrix(int screen_size)
{
//    return LinalMatrix<double>({
//        {(screen_size / 2)},
//    });
}
