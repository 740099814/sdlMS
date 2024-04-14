#ifndef HEADER_SDLMS_MAP
#define HEADER_SDLMS_MAP
#include <vector>
#include <array>
#include <SDL2/SDL.h>

#include "template/currenton.hpp"
#include "sdlms/tile.hpp"
#include "sdlms/obj.hpp"
#include "sdlms/backgrd.hpp"
#include "sdlms/portal.hpp"
#include "sdlms/graphics.hpp"
#include "sdlms/camera.hpp"
#include "sdlms/minimap.hpp"
#include "sdlms/foothold.hpp"
#include "sdlms/ladderRope.hpp"
#include "sdlms/character.hpp"

class Map : public Currenton<Map>
{
public:
    Map();
    void draw();
    void update(int elapsedTime);

public:
    std::array<std::vector<Tile>, 8> _tile;
    std::array<std::vector<Obj>, 8> _obj;
    std::pair<std::vector<BackGrd>, std::vector<BackGrd>> _backgrd; //背景和前景
    std::vector<Portal> _portal;
    std::tuple<std::vector<uint8_t>, int> _sound; // pcm流,采样率
    std::unordered_map<int, FootHold> _foothold;
    std::unordered_map<int, LadderRope> _ladderRope;
};

#endif