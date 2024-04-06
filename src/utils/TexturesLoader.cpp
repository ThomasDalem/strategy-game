#include "TexturesLoader.hpp"

TexturesLoader::TexturesLoader(SDL::Renderer &renderer) : _renderer(renderer)
{}

TexturesLoader::~TexturesLoader()
{}

std::shared_ptr<SDL::Texture> TexturesLoader::getTexture(const std::string &path)
{
    // creates the texture with these arguments if it does not exists
    auto it = _textures.try_emplace(path, std::make_shared<SDL::Texture>(path, _renderer)).first;

    return it->second;
}
