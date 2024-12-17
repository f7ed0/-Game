#include "objects/Point.hpp"
#include <cmath>
#include <cstdlib>
#include <glm/geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

using namespace game3D::objects;

Point::Point() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

Point::Point(const GLfloat *&coord) {
  this->x = *(coord++);
  this->y = *(coord++);
  this->z = *(coord++);
}

Point::Point(Point &p) {
  this->x = p.x;
  this->y = p.y;
  this->z = p.z;
}

GLfloat *Point::toGL() {
  GLfloat *ret = (GLfloat *)malloc(sizeof(GLfloat) * 3);
  ret[0] = this->x;
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

void Point::moveAmount(const Vector &v) {
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
}

void Point::moveTo(GLfloat _x, GLfloat _y, GLfloat _z) {
  this->x = _x;
  this->y = _y;
  this->z = _z;
}

void Point::rotate(Point axis, GLfloat rx, GLfloat ry, GLfloat rz) {
  Point torot = Point::diff(*this, axis);
  glm::vec3 n = glm::rotate(torot, rx, {1, 0, 0});
  n = glm::rotate(n, ry, {0, 1, 0});
  n = glm::rotate(n, rz, {0, 0, 1});
  this->x = axis.x + n.x;
  this->y = axis.y + n.y;
  this->z = axis.z + n.z;
}

Vector Point::diff(const Point &a, const Point &b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

GLfloat Point::getX() const { return this->x; }

GLfloat Point::getY() const { return this->y; }

GLfloat Point::getZ() const { return this->z; }

void Point::modulo(GLfloat modulo) {
  while (this->x > modulo) {
    this->x -= modulo;
  }
  while (this->y > modulo) {
    this->y -= modulo;
  }
  while (this->z > modulo) {
    this->z -= modulo;
  }

  while (this->x < 0) {
    this->x += modulo;
  }
  while (this->y < 0) {
    this->y += modulo;
  }
  while (this->z < 0) {
    this->z += modulo;
  }
}
