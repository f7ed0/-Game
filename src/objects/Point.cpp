#include "objects/Point.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace game3D::objects;

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(const GLfloat*& coord) {
    this->x = *(coord++);
    this->y = *(coord++);
    this->z = *(coord++);
}

Point::Point(Point& p) {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
}

GLfloat* Point::toGL() {
    GLfloat* ret = (GLfloat*) malloc(sizeof(GLfloat)*3);
    ret[0] =  this->x;
    ret[1] = this->y;
    ret[2] = this->z;
    return ret;
}

Point::Point(const GLfloat _x, const GLfloat _y, const GLfloat _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

void Point::moveAmount(GLfloat _dx, GLfloat _dy, GLfloat _dz) {
    this->x += _dx;
    this->y += _dy;
    this->z += _dz;
}

void Point::moveAmount(const Vector& v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
}

void Point::moveTo(GLfloat _x,GLfloat _y,GLfloat _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

void Point::rotate(Point axis, GLfloat rx, GLfloat ry, GLfloat rz) {
    GLfloat cosx,sinx,cosy,siny,cosz,sinz;

    Vector dp = Point::diff(*this,axis);
    Vector angle = {0.0f, 0.0f, 0.0f};

    if(rx == 0) {
        cosx = 1;
        sinx = 0;
    } else {
        cosx = cosf32(rx);
        sinx = sinf32(rx);
    }
    if(ry == 0) {
        cosy = 1;
        siny = 0;
    } else {
        cosy = cosf32(ry);
        siny = sinf32(ry);
    }
    if(rz == 0) {
        cosz = 1;
        sinz = 0;
    } else {
        cosz = cosf32(rz);
        sinz = sinf32(rz);
    }

    GLfloat Axx = cosz*cosy;
    GLfloat Axy = cosz*siny*sinx - sinz*cosx;
    GLfloat Axz = cosz*siny*cosx + sinz*sinx;

    GLfloat Ayx = sinz*cosy;
    GLfloat Ayy = sinz*siny*sinx + cosz*cosx;
    GLfloat Ayz = sinz*siny*cosx - cosz*sinx;

    GLfloat Azx = -siny;
    GLfloat Azy = cosy*sinx;
    GLfloat Azz = cosy*cosx;

    angle.x = Axx*dp.x + Axy*dp.y + Axz*dp.z;
    angle.y = Ayx*dp.x + Ayy*dp.y + Ayz*dp.z;
    angle.z = Azx*dp.x + Azy*dp.y + Azz*dp.z;

    this->moveTo(axis.x,axis.y,axis.z);
    this->moveAmount(angle);
}

Vector Point::diff(const Point& a, const Point& b) {
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}

GLfloat Point::getX() const {
    return this->x;
}

GLfloat Point::getY() const {
    return this->y;
}

GLfloat Point::getZ() const {
    return this->z;
}

void Point::modulo(GLfloat modulo) {
    while(this->x > modulo) {
        this->x -= modulo;
    }
    while(this->y > modulo) {
        this->y -= modulo;
    }
    while(this->z > modulo) {
        this->z -= modulo;
    }
    
    while(this->x < 0) {
        this->x += modulo;
    }
    while(this->y < 0) {
        this->y += modulo;
    }
    while(this->z < 0) {
        this->z += modulo;
    }
}