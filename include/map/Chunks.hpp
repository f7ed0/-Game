#ifndef GAME_MAP_CHUNKS
#define GAME_MAP_CHUNKS

#include <string>
#include "objects/Point.hpp"
#include "objects/Cube.hpp"

namespace game3D::map {
    class Chunks {
        private :
            objects::Point  *coord;
            objects::Cube   **layout;
        protected:
            void generate(unsigned int seed);
        public :
            Chunks();

            Chunks(unsigned int seed, objects::Point& coordinates);

            Chunks(std::string filename);

            void render();
    };
}

#endif