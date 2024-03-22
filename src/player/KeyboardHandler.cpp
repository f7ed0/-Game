#include "player/KeyboardHandler.hpp"

using namespace game3D::player;

KeyboardHandler::KeyboardHandler() {
    this->key_arr[0] = false;
    this->key_arr[1] = false;
    this->key_arr[2] = false;
    this->key_arr[3] = false;
    this->key_arr[4] = false;
    this->translation_key[0] = SDLK_z;
    this->translation_key[1] = SDLK_s;
    this->translation_key[2] = SDLK_q;
    this->translation_key[3] = SDLK_d;
    this->translation_key[4] = SDLK_SPACE;
}

KeyboardHandler::KeyboardHandler(SDL_Keycode translation[KNUM]): KeyboardHandler() {
    for(int i=0 ; i < this->KNUM ; i++) {
        this->translation_key[i] = translation[i];
    }
}

void KeyboardHandler::press(SDL_Keycode key) {
    for(int i=0 ; i < this->KNUM ; i++) {
        if (this->translation_key[i] == key) {
            this->key_arr[i] = true;
        }
    }
}

void KeyboardHandler::release(SDL_Keycode key) {
    for(int i=0 ; i < this->KNUM ; i++) {
        if (this->translation_key[i] == key) {
            this->key_arr[i] = false;
        }
    }
}


bool KeyboardHandler::getState(event event) {
    return this->key_arr[event];
}

bool KeyboardHandler::getState(SDL_Keycode keycode) {
    for(int i=0 ; i < this->KNUM ; i++) {
        if (this->translation_key[i] == keycode) {
            return this->key_arr[i];
        }
    }
    return false;
}