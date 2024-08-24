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
        // Volume between 0 and 128
        int setVolume(int volume);
        // Returns the channel
        int play(int loops = 0, int channel = -1);

    private:
        Mix_Chunk *_chunk;
    };
}

#endif