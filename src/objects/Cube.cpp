#include "objects/Cube.hpp"
#include "logger/Logger.hpp"
#include "graphics/Vertex.hpp"
#include <cmath>
#include <iostream>

using namespace game3D::objects;

Cube::Cube(Point _center, GLfloat _width) {
    this->center = new Point(_center.getX(),_center.getY(),-_center.getZ());
    this->width = _width;
    this->rotation = new Vector();
}

Cube::Cube() {
    this->center = new Point();
    this->width = 0;
    this->rotation = new Vector();
}

void Cube::rotateFrom(Point axis, GLfloat rx, GLfloat ry, GLfloat rz) {
    this->center->rotate(axis,rx,ry,rz);
    this->rotation->moveAmount(rx,ry,rz);
    this->rotation->modulo(2*M_PI);
}

void Cube::rotate(GLfloat rx, GLfloat ry, GLfloat rz) {
    this->rotation->moveAmount(rx,ry,rz);
    this->rotation->modulo(2*M_PI);
}

void Cube::moveAmount(GLfloat dx, GLfloat dy, GLfloat dz) {
    this->center->moveAmount(dx,dy,dz);
}


void Cube::render() {
    graphics::VertexArray *Vertexes = new graphics::VertexArray();

    Point* clones[8];

    for (int i = 0 ; i < 8 ; i++) {
        clones[i] = new Point(*center);
    }

    clones[0]->moveAmount(-width/2,-width/2,width/2);   // 0
    clones[1]->moveAmount(width/2,-width/2,width/2);    // 1
    clones[2]->moveAmount(width/2,width/2,width/2);     // 2
    clones[3]->moveAmount(-width/2,width/2,width/2);    // 3
    clones[4]->moveAmount(-width/2,-width/2,-width/2);  // 4
    clones[5]->moveAmount(width/2,-width/2,-width/2);   // 5
    clones[6]->moveAmount(width/2,width/2,-width/2);    // 6
    clones[7]->moveAmount(-width/2,width/2,-width/2);   // 7

    // Apply rotation
    for (int i = 0 ; i < 8 ; i++) {
        clones[i]->rotate(*this->center,this->rotation->getX(),this->rotation->getY(),this->rotation->getZ());
    }

    GLubyte cubeIndices[24] = {2,3,0,1, 7,6,5,4, 3,2,6,7, 4,5,1,0,
                                  6,2,1,5, 3,7,4,0};


    for (int i = 0 ; i < 24 ; i++) {
        graphics::Vertex v = graphics::Vertex(*(clones[cubeIndices[i]]));
        
        *v.s0 = ((i%4 == 1 || i%4 == 2) ? 1.0f : 0.0f);
        *v.t0 = ((i%4 == 2 || i%4 == 3) ? 1.0 : 0.0f);

        Vertexes->push_back(v);
    } 

    for (int i = 0 ; i < 8 ; i++) {
        delete clones[i];
    }

    GLubyte Indices[4];

    GLfloat* texarr = Vertexes->toTexArr();
    GLfloat* coordarr = Vertexes->toCoordArr();
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1.0f, 1.0f, 1.0f);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glTexCoordPointer(2, GL_FLOAT, 0, texarr);

    glVertexPointer(3, GL_FLOAT, 0, coordarr);

    for(int i = 0 ; i < 6 ; i++) {
        glBindTexture(GL_TEXTURE_2D, this->textures[i]);
        for(int j = 0 ; j < 4 ; j++) {
            Indices[j] = i*4+j;
        }
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, Indices);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    delete Vertexes;
    free(texarr);
    free(coordarr);
}

void Cube::setTexture(Face face, GLuint tex) {
    this->textures[face] = tex;
}

void Cube::setTextures(GLuint texs[]) {
    for(int i = 0 ; i < 6 ; i++) {
        this->textures[i] = texs[i]; 
    }
}