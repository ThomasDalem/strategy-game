#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <string>
#include "SDL2/SDL_mixer.h"

namespace SDL
{
    class MixChunk
    {
    public: 
        MixChunk(const std::string &filename);
        ~MixChunk();

        Mix_Chunk *getChunk();
        void setVolume(int volume);

    private:
        Mix_Chunk *_chunk;
    };
}

#endif