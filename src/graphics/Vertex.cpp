#include "graphics/Vertex.hpp"
#include <cstdlib>

using namespace game3D::graphics;

Vertex::Vertex() {
    this->arr_rep = (GLfloat*) malloc(this->ALLOC_SIZE);
    this->x = arr_rep;
    this->y = arr_rep+1;
    this->z = arr_rep+2;
    this->nx = arr_rep+3;
    this->ny = arr_rep+4;
    this->nz = arr_rep+5;
    this->s0 = arr_rep+6;
    this->t0 = arr_rep+7;
    for(int i=0 ; i < 8 ; i++) {
        this->arr_rep[i] = 0;
    }
}

Vertex::Vertex(GLfloat _x,GLfloat _y,GLfloat _z,GLfloat _nx,GLfloat _ny,GLfloat _nz,GLfloat _s0,GLfloat _t0): Vertex() {
    *x = _x;
    *y = _y;
    *z = _z;
    *nx = _nx;
    *ny = _ny;
    *nz = _nz;
    *s0 = _s0;
    *t0 = _t0;
}

Vertex::Vertex(objects::Point p): Vertex() {
    *x = p.getX();
    *y = p.getY();
    *z = p.getZ();
}

GLfloat* Vertex::toArr() {
    return arr_rep;
}

GLfloat* VertexArray::toCoordArr() {
    GLfloat* ret = (GLfloat *) malloc(sizeof(GLfloat)*3*this->size());
    for ( int i = 0 ; i < this->size() ; i++ ) {
        for( int j = 0 ; j < 3 ; j++) {
            *(ret + i*3 + j) = this->at(i).arr_rep[j];
        }
    }
    return ret;
}

GLfloat* VertexArray::toTexArr() {
    GLfloat* ret = (GLfloat *) malloc(sizeof(GLfloat)*2*this->size());
    for ( int i = 0 ; i < this->size() ; i++ ) {
        for( int j = 0 ; j < 2 ; j++) {
            *(ret + i*2 + j) = this->at(i).arr_rep[6+j];
        }
    }
    return ret;
}