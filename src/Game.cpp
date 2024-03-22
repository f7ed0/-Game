#include <SDL2/SDL_image.h>
#include "Game.hpp"
#include "error/SDLError.hpp"
#include "error/SubsystemNotEnabled.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <logger/Logger.hpp>
#include <cstdlib>
#include <vector>

using namespace game3D;

bool Game::subsystems_enabled = false;

Game::Game() {
    Logger::debug("Starting Game init...");
    this->test = objects::Cube({-7,0,0},4);
    this->test2 = objects::Cube({7,0,0},4);
    this->cam = player::Camera({0,-1,-12},{0,0,0});

    if(!this->subsystemsEnabled()) {
        throw error::SubsystemNotEnabled();
    }
    if(SDL_CreateWindowAndRenderer(1280,720,this->w_flags,&this->w,&this->r) != 0) {
        throw error::SDLError(SDL_GetError());
    }
    SDL_SetWindowTitle(this->w,"µ3Dgame - OpenGL");

    this->running = true;


    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    float ratio = (float) 1280 / (float) 720;

    glEnable(GL_TEXTURE_2D);

    /* Our shading model--Gouraud (smooth). */
    glShadeModel( GL_SMOOTH );

    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );

    /* Set the clear color. */
    glClearColor( 0, 0, 0, 0 );

    /* Setup our viewport. */
    glViewport( 0, 0, 1280, 720 );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    gluPerspective( 90.0, ratio, 1.0, 1024.0 );

    glEnable (GL_DEPTH_TEST);

    Logger::debug("Starting Texture loading...");

    std::vector<const char*> textures_to_load = { "assets/grass_top.png", "assets/grass_side.png", "assets/dirt.png" };

    for(int i = 0 ; i < textures_to_load.size() ; i++) {

        SDL_Surface* s = IMG_Load(textures_to_load.at(i));

        if(s == NULL) {
            throw error::SDLError(IMG_GetError());
        }

        Logger::debug("Creating glTexture...");

        this->texture.push_back((GLuint*) malloc(sizeof(GLuint*)));

        std::cout << *this->texture.back() << std::endl;

        glGenTextures(1, this->texture.back());

        std::cout << *this->texture.back() << std::endl;

        Logger::debug("Binding glTexture...");

        glBindTexture(GL_TEXTURE_2D, *this->texture.back());

        Logger::debug("Feeding surface to gl");

        std::stringstream ss;

        ss << "bpp: " << (int) s->format->BytesPerPixel;

        Logger::debug(ss.str());

        int Mode = GL_RGB;
        if(s->format->BytesPerPixel == 4) {
            Logger::debug("DIRT Texture set to GL_RGBA");
            Mode = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, Mode, s->w, s->h, 0, Mode, GL_UNSIGNED_BYTE, s->pixels);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SDL_FreeSurface(s);

    }



    GLuint t[] = {*this->texture.at(1),*this->texture.at(1),*this->texture.at(0),*this->texture.at(2),*this->texture.at(1),*this->texture.at(1)};

    this->test.setTextures(t);
    this->test2.setTextures(t);

    Logger::info("GAME INIT DONE");
}

Game::~Game() {
    if(r != NULL) {
        SDL_DestroyRenderer(r);
    }
    if(w != NULL) {
        SDL_DestroyWindow(w);
    }
}


void Game::initSubsystems() {
    if(Game::subsystems_enabled) {
        return;
    }
    // TODO enable subsystems
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0) {
        throw error::SDLError(SDL_GetError());
    }
    if(IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG) == 0) {
        throw error::SDLError(IMG_GetError());
    }
    Game::subsystems_enabled = true;
}

void Game::quitSubsystems() {
    IMG_Quit();
    SDL_Quit();
}

bool Game::subsystemsEnabled() {
    return Game::subsystems_enabled;
}