#include "TextureHandler.hpp"

using namespace game3D;

std::map<std::string, GLuint*> *TextureHandler::texture = NULL;

void TextureHandler::init() {
    if (TextureHandler::texture == NULL) {
        TextureHandler::texture = new std::map<std::string, GLuint*>();
    } else {
        throw 0;
    }
}

void TextureHandler::destroy() {
    if (TextureHandler::texture != NULL) {
        delete TextureHandler::texture;
        TextureHandler::texture = NULL;
    } else {
        throw 1;
    }
}

void TextureHandler::setTexture(std::string key, GLuint ref, bool force) {
    if ( texture->find(key) == texture->end() ) {
        texture->emplace(key,ref);
    } else if ( force ) {
        texture->erase(key);
        texture->emplace(key,ref);
    }
}
