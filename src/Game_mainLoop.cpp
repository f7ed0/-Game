#include "Game.hpp"
#include <unistd.h>
#include "logger/Logger.hpp"

using namespace game3D;

void Game::mainLoop() {
    unsigned long counter = 0;
    float frame_time_acc = 0;
    Uint64 oldtiming = SDL_GetTicks64();
    std::stringstream ss;
    float delta;
    while (this->running) {
        oldtiming = this->timing;
        this->timing = SDL_GetTicks64();

        delta = (float) (this->timing - oldtiming)/1000;

        this->eventLoop(delta);
        this->renderLoop(delta);

        frame_time_acc += (float) (SDL_GetTicks64() - timing) / 180;
        if((++ counter)%180 == 0) {
            ss.clear();
            ss << "Mean frametime : "<< frame_time_acc << "ms | Max fps possible : " << 1000/frame_time_acc;
            Logger::debug(ss.str());
            frame_time_acc = 0;
        }

        useconds_t wait_time = (16 - ((useconds_t) (SDL_GetTicks64() - timing)))*1000;

        if(wait_time > 16000){
            ss.clear();
            ss << "Wait time to loong : "<< (float) wait_time / 1000 << "ms";
            Logger::warn(ss.str());
            wait_time = 0;
        }

        usleep(wait_time);
    }
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        ss.clear();
        ss << err;
        Logger::error(ss.str());
    }
    Logger::info("========= MAINLOOP EXITED =======");
} 