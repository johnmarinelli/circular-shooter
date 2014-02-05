/*
* tile to be used in a tilemap
*/
#ifndef _JM_TILE_H
#define _JM_TILE_H

#include "JM_Utilities.h"
#include <string>

namespace JM_Library
{

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int NUMBER_OF_TILETYPES = 12;
const int TOTAL_TILES = 300;

enum JM_TileTypes
{
    LIGHT_BLUE,
    MEDLIGHT_BLUE,
    MEDDARK_BLUE,
    DARK_BLUE,

    LIGHT_RED,
    MEDLIGHT_RED,
    MEDDARK_RED,
    DARK_RED,

    LIGHT_GREEN,
    MEDLIGHT_GREEN,
    MEDDARK_GREEN,
    DARK_GREEN,

    LIGHT_YELLOW,
    MEDLIGHT_YELLOW,
    MEDDARK_YELLOW,
    DARK_YELLOW,
};

struct JM_Tile
{
    JM_TileTypes m_type;
    SDL_Rect m_collisionBox;

    bool m_isCollidable;

    JM_Tile();
    JM_Tile(const JM_Tile& c);

    void init(int x, int y, JM_TileTypes type);

    void update();

    ~JM_Tile();
};

}

#endif