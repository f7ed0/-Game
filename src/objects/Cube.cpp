#include "objects/Cube.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Vertex.hpp"
#include "logger/Logger.hpp"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace game3D::objects;

Cube::Cube(Point _center, GLfloat _width) {
  this->center = new Point(_center.getX(), _center.getY(), _center.getZ());
  this->width = _width;
  this->rotation = new Vector();
}

Cube::Cube() {
  this->center = new Point();
  this->width = 0;
  this->rotation = new Vector();
}

void Cube::rotateFrom(Point axis, GLfloat rx, GLfloat ry, GLfloat rz) {
  this->center->rotate(axis, rx, ry, rz);
  this->rotation->moveAmount(rx, ry, rz);
  this->rotation->modulo(2 * M_PI);
}

void Cube::rotate(GLfloat rx, GLfloat ry, GLfloat rz) {
  this->rotation->moveAmount(rx, ry, rz);
  this->rotation->modulo(2 * M_PI);
}

void Cube::moveAmount(GLfloat dx, GLfloat dy, GLfloat dz) {
  this->center->moveAmount(dx, dy, dz);
}

void Cube::draw(game3D::graphics::Shader& shader) {
  graphics::Mesh toRender;

  for (int i = -1; i <= 1; i += 2) {
    for (int j = -1; j <= 1; j += 2) {
      for (int k = -1; k <= 1; k += 2) {
        Point a(this->center->getX() + k * this->width * 0.5f,
          this->center->getY() + j * this->width * 0.5f,
          this->center->getZ() + i * this->width * 0.5f);
        a.rotate(*this->center, this->rotation->getX(), this->rotation->getY(),
          this->rotation->getZ());
        std::stringstream ss;
        // ss << a.getX() << " " << a.getY() << " " << a.getZ();
        // game3D::Logger::debug(ss.str());
        toRender.vertices.push_back(
          graphics::Vertex(a.getX(), a.getY(), a.getZ(), 0, 0, 0, 0, 0));
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    toRender.vertices.push_back(toRender.vertices.at(i));
  }
  toRender.vertices.push_back(toRender.vertices.at(0));
  toRender.vertices.push_back(toRender.vertices.at(2));
  // game3D::Logger::debug("");
  toRender.vertices.at(0).texcoord = { 0.25, 1 };
  toRender.vertices.at(1).texcoord = { 0.5, 1 };
  toRender.vertices.at(2).texcoord = { 0.25, 0 };
  toRender.vertices.at(3).texcoord = { 0.5, 0 };
  toRender.vertices.at(4).texcoord = { 0.25, 0.667 };
  toRender.vertices.at(5).texcoord = { 0.5, 0.667 };
  toRender.vertices.at(6).texcoord = { 0.25, 0.333 };
  toRender.vertices.at(7).texcoord = { 0.5, 0.333 };

  toRender.vertices.at(8).texcoord = { 0, 0.667 };     // 0
  toRender.vertices.at(9).texcoord = { 0.75, 0.667 };  // 1
  toRender.vertices.at(10).texcoord = { 0, 0.333 };    // 2
  toRender.vertices.at(11).texcoord = { 0.75, 0.333 }; // 3

  toRender.vertices.at(12).texcoord = { 1, 0.667 }; // 0
  toRender.vertices.at(13).texcoord = { 1, 0.333 }; // 2

  /*
     toRender.indices = {
      4, 5, 7, 7, 6, 4, // FRONT FACE
      2, 6, 7, 3, 2, 7, // TOP FACE
      0, 1, 5, 5, 4, 0,// BOTTOM FACE
      0, 3, 1, 3, 0, 2, // BACK FACE
      0, 4, 6, 6, 2, 0, // Left
      1, 7, 5, 7, 1, 3, // Right
  };
  */

  toRender.indices = {
      4,  5,  7, 7,  6,  4,  // FRONT FACE
      2,  6,  7, 3,  2,  7,  // TOP FACE
      0,  1,  5, 5,  4,  0, // BOTTOM FACE
      12, 11, 9, 11, 12, 13, // BACK FACE
      8,  4,  6, 6,  10, 8,  // Left
      9,  7,  5, 7,  9,  11, // Right
  };

  toRender.texture.push_back(this->texture.at(0));

  toRender.draw(shader);
}

void Cube::setTextures(game3D::graphics::Texture tex) {
  if (this->texture.empty()) {
    this->texture.push_back(tex);
  } else {
    this->texture.at(0) = tex;
  }
}
