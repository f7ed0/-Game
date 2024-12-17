#include "error/SDLError.hpp"
#include "logger/Logger.hpp"
#include <GL/gl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <graphics/Texture.hpp>
#include <sstream>

using namespace game3D::graphics;

Texture::Texture(const std::string &path) {
  this->type = "color";
  SDL_Surface *s = IMG_Load(path.c_str());
  if (s == NULL) {
    std::stringstream ss;
    ss << IMG_GetError();
    game3D::Logger::debug(ss.str());
    throw game3D::error::SDLError(IMG_GetError());
  }
  // Logger::debug("CREATING TEXTURE");
  glGenTextures(1, &this->id);
  // std::stringstream ss;
  // ss << "TEX ID : " << this->id;
  // Logger::debug(ss.str());
  // Logger::debug("BINDING TEXTURE");
  glBindTexture(GL_TEXTURE_2D, this->id);

  int mode = GL_RGB;
  if (s->format->BytesPerPixel == 4) {
    mode = GL_RGBA;
  }

  // Logger::debug("LOADING SURFACE INTO GPU...");

  glTexImage2D(GL_TEXTURE_2D, 0, mode, s->w, s->h, 0, mode, GL_UNSIGNED_BYTE,
               s->pixels);

  Logger::debug("Texture Loaded");
  SDL_FreeSurface(s);
}
