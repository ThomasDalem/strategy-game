#include <iostream>
#include "Font.hpp"

using namespace SDL;

Font::Font() : _font(nullptr)
{
    TTF_Init();
}

Font::~Font()
{
    if (_font != nullptr) {
        TTF_CloseFont(_font);
    }
    TTF_Quit();
}

void Font::loadFont(const std::string &filepath, int size)
{
    if (_font != nullptr) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
    _font = TTF_OpenFont(filepath.c_str(), size);
    if (_font == nullptr) {
        throw "Could not load font" + filepath;
    }
}

void Font::setSize(int size)
{
    if (size < 0) {
        std::cerr << "Warning : Trying to set a font size < 0\n";
        return;
    }
    TTF_SetFontSize(_font, size);
}

TTF_Font *Font::getFont()
{
    return _font;
}

bool Font::isLoaded() const
{
    return _font != nullptr;
}
