#ifndef GAME3D_OBJECTS_CUBE_HPP
#define GAME3D_OBJECTS_CUBE_HPP

#include "objects/Point.hpp"

namespace game3D::objects {

    enum Face : GLuint {
        top = 2,
        bottom = 3,
        face = 0,
        back = 1,
        left = 4,
        right = 5,
    };

    class Cube {
        private:
            Point* center;
            GLfloat width;
            Vector* rotation;
            GLuint textures[6];
        public :
            Cube();

            Cube(Point center, GLfloat width);

            void rotate(GLfloat rx, GLfloat ry, GLfloat rz);

            void moveAmount(GLfloat dx, GLfloat dy, GLfloat dz);

            void render();

            void rotateFrom(Point axis, GLfloat rx, GLfloat ry, GLfloat rz);

            void setTexture(Face face, GLuint tex);

            void setTextures(GLuint texs[]);
    };
}

#endif