#ifndef GAME_GRAPHICS_TEXTURE
#define GAME_GRAPHICS_TEXTURE

#include <string>

namespace game3D::graphics {
class Texture {
public:
  unsigned int id;
  std::string type;

  Texture();
};
} // namespace game3D::graphics
#endif
