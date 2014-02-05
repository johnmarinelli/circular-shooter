#include "JM_Tile.h"

namespace JM_Library
{

JM_Tile::JM_Tile()
{
}

JM_Tile::JM_Tile(const JM_Tile& c)
{
    m_type = c.m_type;
    m_collisionBox = c.m_collisionBox;
    m_isCollidable = c.m_isCollidable;
}

void JM_Tile::init(int x, int y, JM_TileTypes type)
{
    m_collisionBox.x = x;
    m_collisionBox.y = y;
    m_collisionBox.w = TILE_WIDTH;
    m_collisionBox.h = TILE_HEIGHT;

    m_type = type;
    m_isCollidable = false;
}

void JM_Tile::update()
{
}

JM_Tile::~JM_Tile()
{
}

}