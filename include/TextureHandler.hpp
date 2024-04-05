#ifndef GAME_TEXTURE_HANDLER
#define GAME_TEXTURE_HANDLER

#include <map>
#include <string>
#include <GL/gl.h>

namespace game3D {

    class TextureHandler {
        private :
            static std::map<std::string, GLuint*> *texture;
        public :
            static void init();
            static void destroy();
            static void setTexture(std::string key, GLuint ref, bool force);
            static GLuint getTexture(std::string key);
    };
}

#endif