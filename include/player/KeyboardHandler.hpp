#ifndef GAME_PLAYER_KEYBOARD_HANDLER
#define GAME_PLAYER_KEYBOARD_HANDLER

#include <SDL2/SDL.h>

namespace game3D::player {

    enum event : short {
        forward,
        back,
        left,
        right,
        jump
    };

    class KeyboardHandler {
        private :
            static const int KNUM = 5;
            SDL_Keycode translation_key[KNUM];
            bool key_arr[KNUM];
        public : 
            KeyboardHandler();

            KeyboardHandler(SDL_Keycode translation[KNUM]);

            void press(SDL_Keycode key);

            void release(SDL_Keycode key);

            bool getState(event event);

            bool getState(SDL_Keycode keycode);
    };
}

#endif