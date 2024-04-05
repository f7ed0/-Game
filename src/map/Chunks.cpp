#include "map/Chunks.hpp"

using namespace game3D::map;

Chunks::Chunks() {
    this->coord = new objects::Point();
    this->layout = NULL;
}

Chunks::Chunks(unsigned int seed, objects::Point& coordinate) {
    this->coord = new objects::Point(coordinate);
    this->generate(seed);
}

void Chunks::generate(unsigned int seed) {
    this->layout = (objects::Cube **) calloc(sizeof(objects::Cube *),256);
    for ( int i = 0 ; i < 16 ; i++ ) {
        for ( int j = 0 ; j < 16 ; j++ ) {
            this->layout[i*16+j] = new objects::Cube({this->coord->getX()*16+i,0,this->coord->getZ()*16+j},1);
        }
    }
}