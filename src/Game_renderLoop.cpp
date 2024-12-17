#include "objects/Cube.hpp"
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

// GLfloat angle = 10.0f;

void Game::renderLoop(float delta) {
  std::stringstream ss;
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    ss << "ERROR::OPENGL::" << "0x" << std::hex << err << "(" << std::dec << err
       << ")";
    Logger::error(ss.str());
  }

  // Logger::debug("Error getter passed");

  /* Clear the color and depth buffers. */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Logger::debug("clear_passed");

  /* We don't want to modify the projection matrix. */
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  glPushMatrix();

  // Logger::debug("Creating cube");

  // glPolygonMode(GL_FRONT, GL_LINE);
  // mesh.draw(this->shader);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  game3D::objects::Cube g({0, 0, -4.0f}, 1.0f);
  // ss.clear();
  // ss << this->textureArr.back().id;
  // Logger::debug("assigning textures");
  // Logger::debug(ss.str());
  g.setTextures(this->textureArr.back());
  // Logger::debug("Rotating");
  g.rotate(M_PI / 4, M_PI / 4 + SDL_GetTicks() * 0.010f, M_PI * 0.18);
  // game3D::Logger::debug("CALLING DRAW");
  g.draw(this->shader);

  SDL_GL_SwapWindow(this->w);
  glPopMatrix();
  // Logger::debug("RENDER LOOP FINISHED");
}
