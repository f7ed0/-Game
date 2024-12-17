#include "Game.hpp"
#include "error/SDLError.hpp"
#include "error/SubsystemNotEnabled.hpp"
#include "graphics/Texture.hpp"
#include "graphics/shader.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <logger/Logger.hpp>
#include <vector>

using namespace game3D;

bool Game::subsystems_enabled = false;

Game::Game() {
  Logger::debug("Starting Game init...");
  // this->test = objects::Cube({-7, 0, 0}, 4);
  // this->test2 = objects::Cube({7, 0, 0}, 4);
  // this->cam = player::Camera({8, 1.6, 8}, {0, 0, 0});

  if (!this->subsystemsEnabled()) {
    throw error::SubsystemNotEnabled();
  }
  if (SDL_CreateWindowAndRenderer(1280, 720, this->w_flags, &this->w,
                                  &this->r) != 0) {
    throw error::SDLError(SDL_GetError());
  }
  SDL_SetWindowTitle(this->w, "µ3Dgame - OpenGL");

  this->running = true;

  std::stringstream ss;

  ss << "USING OPENGL VERSION : " << glGetString(GL_VERSION);

  game3D::Logger::info(ss.str());

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  glEnable(GL_TEXTURE_2D);

  /* Our shading model--Gouraud (smooth). */
  glShadeModel(GL_SMOOTH);

  /* Culling. */
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);

  /* Set the clear color. */
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  /* Setup our viewport. */
  // glViewport(0, 0, 1280.0, 720);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float ratio = 1280.0f / 720.0f;
  gluPerspective(45.0f, ratio, 0.1, 4333);

  glEnable(GL_DEPTH_TEST);

  shader = graphics::Shader("./assets/shaders/vertex1.glslv",
                            "./assets/shaders/fragment1.glslf");

  graphics::Texture t("./assets/bloctex.png");
  textureArr.push_back(t);

  game3D::Logger::info("INIT OK");
}

Game::~Game() {
  if (r != NULL) {
    SDL_DestroyRenderer(r);
  }
  if (w != NULL) {
    SDL_DestroyWindow(w);
  }
}

void Game::initSubsystems() {
  if (Game::subsystems_enabled) {
    return;
  }
  // TODO enable subsystems
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    throw error::SDLError(SDL_GetError());
  }
  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
    throw error::SDLError(IMG_GetError());
  }
  Game::subsystems_enabled = true;
}

void Game::quitSubsystems() {
  IMG_Quit();
  SDL_Quit();
}

bool Game::subsystemsEnabled() { return Game::subsystems_enabled; }
