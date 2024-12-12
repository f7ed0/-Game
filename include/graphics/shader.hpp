#ifndef GAME_GRAPHICS_SHADER
#define GAME_GRAPHICS_SHADER

#include <string>

namespace game3D::graphics {
class Shader {
public:
  unsigned int ID;

  Shader();
  Shader(const char *vertexPath, const char *fragmentPath);

  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
};
} // namespace game3D::graphics

#endif
