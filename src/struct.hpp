#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace stellstructs
{
    const unsigned int D_FILL_REPEAT = 1 << 1;
    const unsigned int D_FILL_STRETCH = 1 << 2;
    const unsigned int D_DISPLAY_ONCE = 1 << 3;
    const unsigned int D_DISPLAY_CENTERED = 1 << 4;
    const unsigned int D_DISPLAY_RIGHT = 1 << 5;

    typedef struct
    {
        int x;
        int y;
        bool percentage;
    } Coordinates;

    typedef struct {
        Coordinates position;
        Coordinates size;
        sf::Texture texture;

        std::string *text;
        Coordinates relativeTextPos;
        sf::Font font;
        int textFlags;
    } Displayable;
}
