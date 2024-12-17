#ifndef GAME_GRAPHICS_TEXTURE
#define GAME_GRAPHICS_TEXTURE

#include <GL/gl.h>
#include <string>

namespace game3D::graphics {
class Texture {
public:
  GLuint id;
  std::string type;

  Texture(const std::string &path);
};
} // namespace game3D::graphics
#endif
