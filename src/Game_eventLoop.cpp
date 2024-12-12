#include "Game.hpp"
#include "logger/Logger.hpp"

using namespace game3D;

bool checksped(player::KeyboardHandler &kb) {
  return (kb.getState(player::forward) xor kb.getState(player::back)) and
         (kb.getState(player::left) xor kb.getState(player::right));
}

void Game::eventLoop(float delta) {
  SDL_Event evt;
  std::stringstream ss;
  while (SDL_PollEvent(&evt)) {

    switch (evt.type) {
    case SDL_QUIT:
      Logger::info("QUIT event triggered");
      this->running = false;
      break;
      ss.clear();
    }
  }
}
