#ifndef GAME_GRAPHICS_MODELLOADER
#define GAME_GRAPHICS_MODELLOADER

#include <assimp/Importer.hpp>
namespace game3D::graphics {
class ModelLoader {
private:
public:
  ModelLoader();
  const aiScene *LoadObject(const std::string &FilePath);
};
} // namespace game3D::graphics

#endif
