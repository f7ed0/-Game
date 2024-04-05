#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "objects/Cube.hpp"
#include "player/Camera.hpp"
#include "player/KeyboardHandler.hpp"

namespace game3D
{
    class Game {
        private :
            static bool subsystems_enabled;
            SDL_Window* w;
            SDL_Renderer* r;
            Uint64 timing = 0;
            objects::Cube test,test2;
            objects::Cube** map;
            std::vector<GLuint*> texture;
            player::Camera cam;
            player::KeyboardHandler kb;
            static const SDL_WindowFlags w_flags = SDL_WINDOW_OPENGL;

        protected :
            bool running;

            void eventLoop(float delta);
            void renderLoop(float delta);
        public :
            /**
             * 
             * @throws game3D::error::SDLError
             * @throws game3D::error::SubsystemNotEnabled
            */
            Game();

            ~Game();

            void mainLoop();

            /**
             * 
             * @throw game3D::error::SDLError
            */
            static void initSubsystems();

            static void quitSubsystems();

            static bool subsystemsEnabled();
    };
}


#endif