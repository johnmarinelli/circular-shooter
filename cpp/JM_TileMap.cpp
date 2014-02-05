#include "JM_TileMap.h"
#include <fstream>

namespace JM_Library
{

typedef std::vector<JM_Tile*> TileVector;

JM_TileMap::JM_TileMap(SDL_Surface* screen, std::string gfxpath, std::string mappath)
    : m_screen(screen), m_GFX(loadImage(gfxpath))
{
    setClips();
    m_tiles.reserve(TOTAL_TILES);
    m_collidableTiles.reserve(TOTAL_TILES);

    readMap(mappath);
}


TileVector JM_TileMap::getCollidables()
{
    return m_collidableTiles;
}

void JM_TileMap::setClips()
{
    m_clips[LIGHT_BLUE].x = 0; m_clips[LIGHT_BLUE].y = 0; m_clips[LIGHT_BLUE].w = TILE_WIDTH; m_clips[LIGHT_BLUE].h = TILE_HEIGHT;
    m_clips[MEDLIGHT_BLUE].x = 32; m_clips[MEDLIGHT_BLUE].y = 0; m_clips[MEDLIGHT_BLUE].w = TILE_WIDTH; m_clips[MEDLIGHT_BLUE].h = TILE_HEIGHT;
    m_clips[MEDDARK_BLUE].x = 64; m_clips[MEDDARK_BLUE].y = 0; m_clips[MEDDARK_BLUE].w = TILE_WIDTH; m_clips[MEDDARK_BLUE].h = TILE_HEIGHT;
    m_clips[DARK_BLUE].x = 98; m_clips[DARK_BLUE].y = 0; m_clips[DARK_BLUE].w = TILE_WIDTH; m_clips[DARK_BLUE].h = TILE_HEIGHT;

    m_clips[LIGHT_RED].x = 0; m_clips[LIGHT_RED].y = 32; m_clips[LIGHT_RED].w = TILE_WIDTH; m_clips[LIGHT_RED].h = TILE_HEIGHT;
    m_clips[MEDLIGHT_RED].x = 32; m_clips[MEDLIGHT_RED].y = 32; m_clips[MEDLIGHT_RED].w = TILE_WIDTH; m_clips[MEDLIGHT_RED].h = TILE_HEIGHT;
    m_clips[MEDDARK_RED].x = 64; m_clips[MEDDARK_RED].y = 32; m_clips[MEDDARK_RED].w = TILE_WIDTH; m_clips[MEDDARK_RED].h = TILE_HEIGHT;
    m_clips[DARK_RED].x = 98; m_clips[DARK_RED].y = 32; m_clips[DARK_RED].w = TILE_WIDTH; m_clips[DARK_RED].h = TILE_HEIGHT;

    m_clips[LIGHT_GREEN].x = 0; m_clips[LIGHT_GREEN].y = 64; m_clips[LIGHT_GREEN].w = TILE_WIDTH; m_clips[LIGHT_GREEN].h = TILE_HEIGHT;
    m_clips[MEDLIGHT_GREEN].x = 32; m_clips[MEDLIGHT_GREEN].y = 64; m_clips[MEDLIGHT_GREEN].w = TILE_WIDTH; m_clips[MEDLIGHT_GREEN].h = TILE_HEIGHT;
    m_clips[MEDDARK_GREEN].x = 64; m_clips[MEDDARK_GREEN].y = 64; m_clips[MEDDARK_GREEN].w = TILE_WIDTH; m_clips[MEDDARK_GREEN].h = TILE_HEIGHT;
    m_clips[DARK_GREEN].x = 98; m_clips[DARK_GREEN].y = 64; m_clips[DARK_GREEN].w = TILE_WIDTH; m_clips[DARK_GREEN].h = TILE_HEIGHT;

    m_clips[LIGHT_YELLOW].x = 0; m_clips[LIGHT_YELLOW].y = 98; m_clips[LIGHT_YELLOW].w = TILE_WIDTH; m_clips[LIGHT_YELLOW].h = TILE_HEIGHT;
    m_clips[MEDLIGHT_YELLOW].x = 32; m_clips[MEDLIGHT_YELLOW].y = 98; m_clips[MEDLIGHT_YELLOW].w = TILE_WIDTH; m_clips[MEDLIGHT_YELLOW].h = TILE_HEIGHT;
    m_clips[MEDDARK_YELLOW].x = 64; m_clips[MEDDARK_YELLOW].y = 98; m_clips[MEDDARK_YELLOW].w = TILE_WIDTH; m_clips[MEDDARK_YELLOW].h = TILE_HEIGHT;
    m_clips[DARK_YELLOW].x = 98; m_clips[DARK_YELLOW].y = 98; m_clips[DARK_YELLOW].w = TILE_WIDTH; m_clips[DARK_YELLOW].h = TILE_HEIGHT;
}

bool JM_TileMap::readMap(std::string path) 
{
    int xitr = 0, yitr = 0;
    std::ifstream map(path);

    if(map.fail()){
        map.close();
        return false;
    }

    else
    {
        for(int i = 0; i < TOTAL_TILES; ++i){
            int tiletype = -1;
            map >> tiletype;

            if (tiletype >= 0 && tiletype < NUMBER_OF_TILETYPES)
            {
                JM_Tile* tile = new JM_Tile();
                tile->init(xitr, yitr, (JM_TileTypes)tiletype);
                m_tiles.push_back(tile);

                //collidable tile
                if(tiletype >= LIGHT_RED && tiletype < DARK_YELLOW){
                    tile->m_isCollidable = true;
                    m_collidableTiles.push_back(tile);
                }
            }

            //we don't recognize tile type
            else{
                map.close();
                return false;
            }
            
            xitr += TILE_WIDTH;

            //when x has reached the end of a row (change 640 to a const)
            if(xitr >= TILEMAP_WIDTH){
                xitr = 0;
                yitr += TILE_HEIGHT;
            }
        }

        map.close();
        return true;
    }
}

void JM_TileMap::update()
{
}

void JM_TileMap::render()
{
    //erase previous drawings by applying black background
    SDL_FillRect(m_screen, &m_screen->clip_rect, SDL_MapRGB(m_screen->format, 0x00, 0x00, 0x00));

    TileIterator itr = m_tiles.begin();

    for(; itr < m_tiles.end(); ++itr){
        applySurface((*itr)->m_collisionBox.x, (*itr)->m_collisionBox.y, m_GFX, m_screen, &m_clips[(*itr)->m_type]);
    }
}

JM_TileMap::~JM_TileMap()
{
    TileIterator itr = m_tiles.begin();

    //what do with m_screen???
    for(; itr < m_tiles.end(); ++itr){
        delete (*itr);
        (*itr) = NULL;
        m_tiles.erase(itr++);
    }
}

}