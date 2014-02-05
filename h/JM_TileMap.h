/*
* handles a 2D array of tiles to render onto screen
*/
#ifndef _JM_TILEMAP_H
#define _JM_TILEMAP_H

#include <vector>
#include "JM_Tile.h"

namespace JM_Library
{

const int TILEMAP_WIDTH = 640;
const int TILEMAP_HEIGHT = 480;
    
class JM_TileMap
{
private:
    typedef std::vector<JM_Tile*> TileVector;
    typedef TileVector::iterator TileIterator;

    SDL_Surface* m_screen;
    SDL_Surface* m_GFX;

    TileVector m_collidableTiles;
    TileVector m_tiles;
    
    SDL_Rect m_clips[NUMBER_OF_TILETYPES];
    
    bool readMap(std::string path);
    
public:
    JM_TileMap(SDL_Surface* screen, std::string path, std::string mappath);

    std::vector<JM_Tile*> getCollidables();

    void setClips();

    void update();
    void render();

    ~JM_TileMap();
};

}

#endif