#include "graphics/Vertex.hpp"
#include <cstdlib>

using namespace game3D::graphics;

Vertex::Vertex() {
  this->pos = glm::vec3();
  this->normal = glm::vec3();
  this->texcoord = glm::vec2();
}

Vertex::~Vertex() {
  /*if (this->arr_rep != NULL) {
      free(this->arr_rep);
      this->arr_rep = NULL;
  }*/
}

Vertex::Vertex(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _nx, GLfloat _ny,
               GLfloat _nz, GLfloat _s0, GLfloat _t0) {
  this->pos = glm::vec3(_x, _y, _z);
  this->normal = glm::vec3(_nx, _ny, _nz);
  this->texcoord = glm::vec2(_s0, _t0);
}

Vertex::Vertex(objects::Point p) : Vertex() {
  this->pos = glm::vec3(p.getX(), p.getY(), p.getZ());
}

GLfloat *Vertex::toArr() {
  GLfloat *ret = (GLfloat *)malloc(sizeof(GLfloat) * 8);

  ret[0] = this->pos.x;
  ret[1] = this->pos.y;
  ret[2] = this->pos.z;
  ret[3] = this->normal.x;
  ret[4] = this->normal.y;
  ret[5] = this->normal.z;
  ret[6] = this->texcoord.x;
  ret[7] = this->texcoord.y;

  return ret;
}

GLfloat *VertexArray::toCoordArr() {
  GLfloat *ret = (GLfloat *)malloc(sizeof(GLfloat) * 3 * this->size());
  for (int i = 0; i < (int)this->size(); i++) {
    *(ret + i * 3) = this->at(i).pos.x;
    *(ret + i * 3 + 1) = this->at(i).pos.y;
    *(ret + i * 3 + 2) = this->at(i).pos.z;
  }
  return ret;
}

GLfloat *VertexArray::toTexArr() {
  GLfloat *ret = (GLfloat *)malloc(sizeof(GLfloat) * 2 * this->size());
  for (int i = 0; i < (int)this->size(); i++) {
    *(ret + i * 2) = this->at(i).texcoord.x;
    *(ret + i * 2 + 1) = this->at(i).texcoord.y;
  }
  return ret;
}

int VertexArray::toArr(GLfloat **ret) {
  *ret = (GLfloat *)malloc(sizeof(GLfloat) * 8 * this->size());
  if (*ret == NULL) {
    return 0;
  }
  for (unsigned int i = 0; i < this->size(); i++) {
    *(*ret + i * 8) = this->at(i).pos.x;
    *(*ret + i * 8 + 1) = this->at(i).pos.y;
    *(*ret + i * 8 + 2) = this->at(i).pos.z;
    *(*ret + i * 8 + 3) = this->at(i).normal.x;
    *(*ret + i * 8 + 4) = this->at(i).normal.y;
    *(*ret + i * 8 + 5) = this->at(i).normal.z;
    *(*ret + i * 8 + 6) = this->at(i).texcoord.x;
    *(*ret + i * 8 + 7) = this->at(i).texcoord.y;
  }
  return 8 * this->size();
}
