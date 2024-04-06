#ifndef TEXTURESLOADER_HPP
#define TEXTURESLOADER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include "SDL/Texture.hpp"

class TexturesLoader
{
public:
    TexturesLoader(SDL::Renderer &renderer);
    ~TexturesLoader();

    std::shared_ptr<SDL::Texture> getTexture(const std::string &path);

private:
    std::unordered_map<std::string, std::shared_ptr<SDL::Texture>> _textures;
    SDL::Renderer &_renderer;
};

#endif // TEXTURESLOADER_HPP