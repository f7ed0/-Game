#ifndef ERROR_SDLERR_HPP
#define ERROR_SDLERR_HPP

#include "error/GameError.hpp"

namespace game3D::error
{
    class SDLError : public GameError {
        protected :
            char* value;
        public :
            SDLError(const char* value);
            std::string getError() override;
    };
} // namespace game3D



#endif