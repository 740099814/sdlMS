#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <string>
#include "wz/Property.hpp"
#include "Component.h"

class Sprite : public Component
{
public:
    Sprite(SDL_Texture *texture, int width, int height);
    Sprite(wz::Node *node, int alpha = 255);
    ~Sprite();

private:
    Sprite(){};

public:
    const auto get_width() { return width; }
    const auto get_height() { return height; }
    SDL_Texture *get_texture() { return texture; }

    const auto get_delay() { return delay; }
    const auto get_a0() { return a0; }
    const auto get_a1() { return a1; }
    const auto get_origin() { return origin; }

    const auto get_z() { return z; }

public:
    SDL_Texture *texture = nullptr;
    int width = 0;
    int height = 0;

    int delay = 0;
    int a0 = 255;
    int a1 = 255;
    SDL_Point origin = {0, 0};

    int z = 0;
};