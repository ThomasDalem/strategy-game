#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include "SDL/Texture.hpp"
#include "utils/TexturesLoader.hpp"
#include "HUD/Component.hpp"

namespace HUD
{
    class Image: public Component
    {
    public:
        Image(const std::string &filepath, TexturesLoader &textureLoader, int x = 0, int y = 0);
        Image(const std::shared_ptr<SDL::Texture> &texture, int x = 0, int y = 0);

        void draw(SDL::Renderer &renderer);

    protected:
        std::shared_ptr<SDL::Texture> _texture;
    };
}

#endif // IMAGE_HPP