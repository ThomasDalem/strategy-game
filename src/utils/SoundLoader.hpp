#ifndef SOUND_LOADER_HPP
#define SOUND_LOADER_HPP

#include <unordered_map>
#include <string>
#include <boost/json.hpp>

#include "SDL/Chunk.hpp"

class SoundLoader
{
public:
    static SoundLoader &getInstance() {
        static SoundLoader instance;

        return instance;
    };
    SoundLoader(const SoundLoader &other) = delete;
    void operator=(const SoundLoader &other) = delete;

    SDL::MixChunk *loadChunk(const std::string &name);
    SDL::MixChunk *loadRandomChunk(std::string &group);

private:
    SoundLoader();

    boost::json::value parseJSON(const std::string &filepath);

    std::unordered_map<std::string, SDL::MixChunk> _chunks;
    boost::json::value _json;
};

#endif