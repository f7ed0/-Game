#define GL_GLEXT_PROTOTYPES

#include "graphics/Mesh.hpp"
#include "graphics/Vertex.hpp"
#include "logger/Logger.hpp"
#include <GL/gl.h>
#include <GL/glext.h>

using namespace game3D::graphics;

Mesh::Mesh(const VertexArray &vertices,
           const std::vector<unsigned int> &indices,
           const std::vector<Texture> &texture) {
  this->vertices = vertices;
  this->indices = indices;
  this->texture = texture;
}

void Mesh::draw(Shader &shader) {
  float *vertices;

  int len = this->vertices.toArr(&vertices);

  if (len == 0) {
    game3D::Logger::error("Error initiating vertex array");
    return;
  }

  GLuint *indices = (GLuint *)calloc(sizeof(GLuint), this->indices.size());
  if (indices == NULL) {
    game3D::Logger::error("Error initiating indices array");
    return;
  }

  for (unsigned i = 0; i < this->indices.size(); i++) {
    indices[i] = this->indices.at(i);
  }

  // game3D::Logger::debug("Indices cloned");
  glEnableClientState(GL_VERTEX_ARRAY);
  unsigned int VAO, VBO;

  // VERTICE BUFFER
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * len, vertices, GL_STATIC_DRAW);

  // game3D::Logger::debug("Buffers ready");

  // VERTEX ARRAY
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // POSITION
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // NORMAL
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // TEXCOORD
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // game3D::Logger::debug("VertexArray ready");

  shader.use();

  // game3D::Logger::debug("Shader used");
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, indices);
  // glBindVertexArray(0);
  glDisableClientState(GL_VERTEX_ARRAY);

  glUseProgram(0);

  free(vertices);
  free(indices);
}
