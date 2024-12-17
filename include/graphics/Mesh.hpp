#ifndef GAME_GRAPHICS_MESH
#define GAME_GRAPHICS_MESH

#include "graphics/Texture.hpp"
#include "graphics/Vertex.hpp"
#include "graphics/shader.hpp"
#include <vector>
namespace game3D::graphics {
class Mesh {
public:
  VertexArray vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> texture;

  Mesh();

  Mesh(const VertexArray &vertices, const std::vector<unsigned int> &indices,
       const std::vector<Texture> &texture);

  void draw(Shader &shader);
};
} // namespace game3D::graphics

#endif
