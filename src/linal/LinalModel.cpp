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
        glVertex3d(
            draw_vertices.values[x][vert_index],
            draw_vertices.values[y][vert_index],
            draw_vertices.values[z][vert_index]
        );
    }
    glEnd();
}

LinalMatrix<double> LinalModel::get_screenspace_matrix(CameraMatrix& camera, PerspectiveMatrix& perspective)
{
    // Reason perspective and camera are not multiplied beforehand is because in the real world, the camera matrix can
    // change. This prohibits us from calculating perspective * camera in advance.
    LinalMatrix<double> non_corrected_matrix = perspective.get_matrix() * camera.get_matrix() * *this;

    vector<double> x_vec;
    vector<double> y_vec;
    vector<double> z_vec;

    for (size_t vert_index = 0; vert_index < non_corrected_matrix.x_size; vert_index++) {
        if (non_corrected_matrix.values[w][vert_index] > 0) {
            x_vec.push_back(this->_get_corrected_coord(non_corrected_matrix.values[x][vert_index], non_corrected_matrix.values[w][vert_index], 640));
            y_vec.push_back(this->_get_corrected_coord(non_corrected_matrix.values[y][vert_index], non_corrected_matrix.values[w][vert_index], 640));
            z_vec.push_back(this->_get_corrected_coord(non_corrected_matrix.values[z][vert_index], non_corrected_matrix.values[w][vert_index], 1000));
        }
    }

    return LinalMatrix<double>({x_vec, y_vec, z_vec});
}

double LinalModel::_get_corrected_coord(double coordinate, double w, double axis_length)
{
    double half_axis = axis_length / 2;

    return half_axis + ((coordinate + 1) / w) * half_axis;
}
