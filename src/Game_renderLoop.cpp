#include <ios>
#define GL_GLEXT_PROTOTYPES

#include "Game.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Vertex.hpp"
#include "logger/Logger.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl_glext.h>
#include <SDL2/SDL_timer.h>
#include <sstream>

using namespace game3D;

GLfloat angle = 10.0f;

void Game::renderLoop(float delta) {
  std::stringstream ss;
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    ss << "ERROR::OPENGL::" << "0x" << std::hex << err << "(" << std::dec << err
       << ")";
    Logger::error(ss.str());
  }

  /* Clear the color and depth buffers. */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* We don't want to modify the projection matrix. */
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  glPushMatrix();

  game3D::graphics::VertexArray vertices;
  vertices.push_back(game3D::graphics::Vertex(-0.5f, -0.5f, -10.0f, 0.0f, 0.0f,
                                              0.0f, 0.0f, 0.0f));
  vertices.push_back(game3D::graphics::Vertex(0.5f, -0.5f, -10.0f, 0.0f, 0.0f,
                                              0.0f, 0.0f, 0.0f));
  vertices.push_back(game3D::graphics::Vertex(0.5f, 0.5f, -10.0f, 0.0f, 0.0f,
                                              0.0f, 0.0f, 0.0f));
  vertices.push_back(game3D::graphics::Vertex(-0.5f, 0.5f, -10.0f, 0.0f, 0.0f,
                                              0.0f, 0.0f, 0.0f));
  std::vector<unsigned int> indices;
  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);
  indices.push_back(2);
  indices.push_back(3);
  indices.push_back(0);
  std::vector<graphics::Texture> textures;

  graphics::Mesh mesh(vertices, indices, textures);

  // glPolygonMode(GL_FRONT, GL_LINE);
  mesh.draw(this->shader);

  SDL_GL_SwapWindow(this->w);
  glPopMatrix();
}
