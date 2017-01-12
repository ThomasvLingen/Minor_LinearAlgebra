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
    // We copy the model here so that we only apply the camera and perspective matrix for this draw call.
    // This way, we don't actually transform the vertices of the object.
    std::cout << "Camera: " << std::endl;
    camera.get_matrix().print();
    std::cout << "Perspective: " << std::endl;
    perspective.get_matrix().print();
    LinalModel draw_vertices = this->get_screenspace_matrix(camera, perspective);
    std::cout << "Original: " << std::endl;
    this->print();
    std::cout << "Draw_verts: " << std::endl;
    draw_vertices.print();

    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_LINES); // The model is drawn using lines
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    // We unfortunately can't range based for here
    for (size_t vert_index = 0; vert_index < draw_vertices.x_size; vert_index++) {
        if (draw_vertices.values[2][vert_index] > 0) {
            glVertex3d(
                320 + ((draw_vertices.values[0][vert_index] + 1) / (draw_vertices.values[2][vert_index] + 0.00000001)) * 320,
                320 + ((draw_vertices.values[1][vert_index] + 1) / (draw_vertices.values[2][vert_index] + 0.00000001)) * 320,
                -(draw_vertices.values[3][vert_index]) // TODO: this should be index 2, but for some reason the z values are at index 3 (where normally the z would be)
            );
        }
    }
    glEnd();
}

LinalMatrix<double> LinalModel::get_screenspace_matrix(CameraMatrix& camera, PerspectiveMatrix& perspective)
{
    return camera.get_matrix() * perspective.get_matrix() * *this;
}

LinalMatrix<double> LinalModel::get_correction_matrix(int screen_size)
{
//    return LinalMatrix<double>({
//        {(screen_size / 2)},
//    });
}
