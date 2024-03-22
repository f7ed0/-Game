#ifndef ERROR_GAMEERR_HPP
#define ERROR_GAMEERR_HPP

#include <string>

namespace game3D::error
{
    class GameError {
        public :
        virtual std::string getError() {
            return "";
        }
    };
} // namespace game3D



#endif