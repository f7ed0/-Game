#include "Game.hpp"
#include "logger/Logger.hpp"

using namespace game3D;

bool checksped(player::KeyboardHandler& kb) {
    return (kb.getState(player::forward) xor kb.getState(player::back)) and (kb.getState(player::left) xor kb.getState(player::right));
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
        case SDL_KEYDOWN :
            this->kb.press(evt.key.keysym.sym);
            break;
        case SDL_KEYUP :
            this->kb.release(evt.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION :
            this->cam.rotateLock({(GLfloat) evt.motion.yrel*0.01f, (GLfloat) evt.motion.xrel*0.01f,0});
            //this->cam.rotate({(GLfloat) evt.motion.yrel*0.01f, (GLfloat) evt.motion.xrel*0.01f,0});
            //ss << this->cam.getRotX() << " " << this->cam.getRotY() << " " << this->cam.getRotZ();
            //Logger::debug(ss.str());
            SDL_WarpMouseInWindow(this->w, 640, 360);
            break;
        }
        ss.clear();
    }
    GLfloat spd = checksped(this->kb) ? 2.5f*0.7f : 2.5f*1.0f;
    spd *= delta;

    objects::Vector v(
        (this->kb.getState(player::right) ? spd : 0.0f) + (this->kb.getState(player::left) ? -spd : 0.0f),
        0,
        (this->kb.getState(player::forward) ? spd : 0.0f) + (this->kb.getState(player::back) ? -spd : 0.0f)
    );
    v.rotate({0,0,0},0,this->cam.getRotY(),0);
    //ss << v.getX() << " " << v.getY() << " " << v.getZ() << "|";
    this->cam.move(v);
    //ss << this->cam.getPosX() << " " << this->cam.getPosY() << " " << this->cam.getPosZ();
    //Logger::debug(ss.str());
}

