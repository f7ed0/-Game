#include "Game.hpp"
#include "error/SDLError.hpp"
#include "graphics/shader.hpp"
#include "logger/Logger.hpp"
#include <GL/gl.h>
#include <GL/glut.h>
// #include <iostream>

using namespace std;

void logGL();

int main() {

  game3D::Logger::setLogLevel(game3D::LogLevel::debug);

  try {

    game3D::Game::initSubsystems();

    game3D::Game *a = new game3D::Game();

    // game3D::graphics::Shader s("a", "b");

    a->mainLoop();

    game3D::Logger::debug("Deleting a...");
    delete a;

    game3D::Logger::debug("done !");

    game3D::Game::quitSubsystems();

  } catch (game3D::error::SDLError &e) {
    game3D::Logger::error(e.getError());
    exit(1);
  }

  game3D::Logger::info("Game exited normally.");

  return 0;
}
