#ifndef GAME_GRAPHICS_VERTEX
#define GAME_GRAPHICS_VERTEX

#include <GL/gl.h>
#include <vector>

#include "objects/Point.hpp"

namespace game3D::graphics {
    class Vertex {
        public :
            GLfloat* arr_rep;

            GLfloat *x,*y,*z;
            GLfloat *nx,*ny,*nz;
            GLfloat *s0,*t0;

            static const int ALLOC_SIZE = sizeof(GLfloat)*8;

            Vertex();
            Vertex(GLfloat x,GLfloat y,GLfloat z,GLfloat nx,GLfloat ny,GLfloat nz,GLfloat s0,GLfloat t0);

            Vertex(objects::Point p);

            ~Vertex();

            GLfloat* toArr();

    };

    class VertexArray : public std::vector<Vertex> {
        public :
            GLfloat* toCoordArr();
            GLfloat* toTexArr();
    };
} // namespace game3D::graphics


#endif