#include "SoundLoader.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

#include "utils/Random.hpp"

namespace json = boost::json;

SoundLoader::SoundLoader()
{
    _json = parseJSON("../data/sound.json");
}


boost::json::value SoundLoader::parseJSON(const std::string &filepath)
{
    json::stream_parser parser;
    boost::system::error_code ec;
    std::ifstream stream(filepath, std::ios::binary);

    if (!stream.is_open())
    {
        std::cout << "Failed to open: " << filepath << "\n";
        throw("Opening error");
    }

    do
    {
        char buf[4096];
        stream.read(buf, sizeof(buf));
        std::streamsize nbRead = stream.gcount();
        parser.write(buf, nbRead, ec);
    } while (stream.eof() == false);

    if (ec)
    {
        std::cout << "Error while reading JSON file: " << ec.message() << "\n";
        throw("Reading error");
    }
    parser.finish();
    if (ec)
    {
        std::cout << "Error while parsing JSON file: " << ec.message() << "\n";
        throw("Parsing error");
    }
    return parser.release();
}

SDL::MixChunk *SoundLoader::loadChunk(const std::string &name)
{
    if (_chunks.find(name) != _chunks.end())
    {
        return &_chunks.at(name);
    }

    const json::array &sounds = _json.at("all").as_array();
    auto it = std::find_if(sounds.begin(), sounds.end(), [name](const json::value &obj){
        return obj.at("name").as_string() == name;
    });

    if (it == sounds.end())
    {
        std::cout << "Audio with name: " << name << " is unknown\n";
        return nullptr;
    }

    std::string filepath("../");
    filepath += it->as_object().at("filepath").as_string();

    SDL::MixChunk &chunk = _chunks.emplace(name, filepath).first->second;
    if (it->as_object().if_contains("vol"))
    {
        const int vol = it->as_object().at("vol").as_int64();
        chunk.setVolume(vol);
    }

    return &chunk;
}

SDL::MixChunk *SoundLoader::loadRandomChunk(std::string &group)
{
    boost::system::error_code ec;
    json::value *val = _json.find_pointer(group, ec);

    if (val == nullptr)
    {
        std::cerr << "Pointed value could not be found: " << ec.message() << " - " << group << "\n";
        return nullptr;
    }
    if (val->is_array() == false)
    {
        std::cerr << "Pointed value is not an array: " << group << "\n";
        return nullptr;
    }

    const json::array &sounds = val->as_array();
    RandomInt random(0, sounds.size() - 1);
    const json::object &obj = sounds.at(random.generate()).as_object();

    std::string filepath("../");
    filepath += obj.at("filepath").as_string();

    SDL::MixChunk &chunk = _chunks.emplace(obj.at("name").as_string(), filepath).first->second;
    if (obj.if_contains("vol"))
    {
        const int vol = obj.at("vol").as_int64();
        chunk.setVolume(vol);
    }

    return &chunk;
}
