#include "Game.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <sstream>
#include "logger/Logger.hpp"


using namespace game3D;

GLfloat angle = 10.0f;

void Game::renderLoop() {
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        std::stringstream ss;

        ss << err;

        Logger::error(ss.str());
    }

    /* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    /* Rotate. */
    glRotatef( (this->cam.getRotX()*360.0f)/(M_PI*2), 1, 0.0, 0.0 );
    glRotatef( (this->cam.getRotY()*360.0f)/(M_PI*2), 0.0, 1, 0.0 );
    glRotatef( (this->cam.getRotZ()*360.0f)/(M_PI*2), 0.0, 0.0, 1 );

    glTranslatef(-this->cam.getPosX(), this->cam.getPosY(), this->cam.getPosZ() );


    this->test.rotate(0, 0.01 , 0);
    this->test2.rotate(0.01,0.00,0.01);

    //this->test.rotateFrom({0,0,0},0,0.02,0);
    //this->test2.rotateFrom({0,0,0},0,0.02,0);

    this->test.render();

    this->test2.render();


    SDL_GL_SwapWindow(this->w);


}