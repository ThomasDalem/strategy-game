#include "Chunk.hpp"

#include <iostream>

using namespace SDL;

MixChunk::MixChunk(const std::string &filename)
    : _chunk(Mix_LoadWAV(filename.c_str()))
{
    if (_chunk == nullptr)
    {
        std::cerr << "Could not load wav file " << filename << " : " << Mix_GetError() << "\n";
    }
}

MixChunk::~MixChunk()
{
    if (_chunk)
    {
        Mix_FreeChunk(_chunk);
    }
}

Mix_Chunk *MixChunk::getChunk()
{
    return _chunk;
}

int MixChunk::setVolume(int volume)
{
    return Mix_VolumeChunk(_chunk, volume);
}

int MixChunk::play(int loops, int channel)
{
    if (_chunk == nullptr)
    {
        std::cerr << "Trying to play null chunk\n";
    }
    return Mix_PlayChannel(channel, _chunk, loops);
}
