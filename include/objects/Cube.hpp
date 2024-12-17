#ifndef GAME3D_OBJECTS_CUBE_HPP
#define GAME3D_OBJECTS_CUBE_HPP

#include "graphics/Texture.hpp"
#include "graphics/shader.hpp"
#include "objects/Point.hpp"
#include <vector>

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
  Point *center;
  GLfloat width;
  Vector *rotation;
  std::vector<game3D::graphics::Texture> texture;

public:
  Cube();

  Cube(Point center, GLfloat width);

  void rotate(GLfloat rx, GLfloat ry, GLfloat rz);

  void moveAmount(GLfloat dx, GLfloat dy, GLfloat dz);

  void draw(game3D::graphics::Shader &shader);

  void rotateFrom(Point axis, GLfloat rx, GLfloat ry, GLfloat rz);

  void setTextures(game3D::graphics::Texture tex);
};
} // namespace game3D::objects

#endif
