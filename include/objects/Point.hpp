#ifndef GAME3D_OBJECTS_POINT_HPP
#define GAME3D_OBJECTS_POINT_HPP

#include <GL/gl.h>

namespace game3D::objects {
    class Point;

    typedef Point Vector;    

    class Point {
        private :
            GLfloat x,y,z;
        public :
            Point();

            Point(Point& p);

            Point(const GLfloat*& coord);

            Point(const GLfloat x, const GLfloat y, const GLfloat z);

            GLfloat* toGL();

            void modulo(GLfloat modulo);

            void moveAmount(GLfloat dx, GLfloat dy, GLfloat dz);

            void moveAmount(const Vector& v);

            void moveTo(GLfloat x,GLfloat y,GLfloat z);

            void rotate(Point axis, GLfloat rx, GLfloat ry, GLfloat rz);

            GLfloat getX() const;

            GLfloat getY() const;

            GLfloat getZ() const;


            /**
            * Returns the vector of the difference between the two points 
            */
            static Vector diff(const Point& a, const Point& b);

    };



}



#endif