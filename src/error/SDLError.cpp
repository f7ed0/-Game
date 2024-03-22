#include "error/SDLError.hpp"

using namespace game3D::error;

SDLError::SDLError(const char* __value) {
    this->value = (char*) __value;
}

std::string SDLError::getError() {
    return this->value;
}