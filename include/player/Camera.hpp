#ifndef GAME_PLAYER_CAMERA_HPP

#define GAME_PLAYER_CAMERA_HPP

#include "objects/Point.hpp"

namespace game3D::player {
    class Camera {
        private :
            objects::Point position;
            objects::Vector angle;
        public :
            Camera();

            Camera(const objects::Point __position, const objects::Vector __angle);

            void rotate(const objects::Vector angle);
            void rotateLock(const objects::Vector angle);

            void move(const objects::Vector amount);

            void tp(const objects::Point new_postion);

            GLfloat getPosX();
            GLfloat getPosY();
            GLfloat getPosZ();

            GLfloat getRotX();
            GLfloat getRotY();
            GLfloat getRotZ();
            
    };
}

#endif