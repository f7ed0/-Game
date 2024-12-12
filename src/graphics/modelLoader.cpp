#include "graphics/modelLoader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

using namespace game3D::graphics;

ModelLoader::ModelLoader() {}

const aiScene *ModelLoader::LoadObject(const std::string &FilePath) {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
      FilePath, aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                    aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

  return scene;
}
