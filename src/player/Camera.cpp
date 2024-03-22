#include <cmath>
#include "logger/Logger.hpp"
#include "player/Camera.hpp"

using namespace game3D::player;

Camera::Camera() {
    this->position = objects::Point();
    this->angle = objects::Vector();
}

Camera::Camera(objects::Point __position, objects::Vector __angle) {
    this->position = objects::Point(__position);
    this->angle = objects::Vector(__angle);

}

void Camera::rotate(objects::Vector angle) {
    this->angle.moveAmount(angle);
    this->angle.modulo(M_PI*2);
}

void Camera::move(objects::Vector amount) {
    this->position.moveAmount(amount);
}

void Camera::tp(const objects::Point new_position) {
    this->position.moveTo(new_position.getX(),new_position.getY(), new_position.getZ());
}

GLfloat Camera::getPosX() {
    return this->position.getX();
}
GLfloat Camera::getPosY() {
    return this->position.getY();
}
GLfloat Camera::getPosZ() {
    return this->position.getZ();
}

GLfloat Camera::getRotX() {
    return this->angle.getX();
}
GLfloat Camera::getRotY() {
    return this->angle.getY();
}
GLfloat Camera::getRotZ() {
    return this->angle.getZ();
}