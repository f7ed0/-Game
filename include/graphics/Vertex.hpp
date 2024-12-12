#ifndef GAME_GRAPHICS_VERTEX
#define GAME_GRAPHICS_VERTEX

#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

#include "objects/Point.hpp"

namespace game3D::graphics {
class Vertex {
public:
  glm::vec3 pos;
  glm::vec3 normal;
  glm::vec2 texcoord;

  Vertex();
  Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz,
         GLfloat s0, GLfloat t0);

  Vertex(objects::Point p);

  ~Vertex();

  GLfloat *toArr();
};

class VertexArray : public std::vector<Vertex> {
public:
  GLfloat *toCoordArr();
  GLfloat *toTexArr();
  int toArr(GLfloat **ret);
};
} // namespace game3D::graphics

#endif
