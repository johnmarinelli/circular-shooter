/*
* game class.  there will be only one instance of this through the program.
* holds data essential throughout the span of the game.
*/

#ifndef _JM_GAME_H
#define _JM_GAME_H

#include "JM_World.h"
#include "JM_WorldGUIInterface.h"
#include "JM_PlayerStats.h"

namespace JM_Library
{

class JM_Game
{
private:
    SDL_Surface* m_screen;
    unsigned int m_level;

    JM_PlayerStats m_playerStats;

    JM_World m_world;
    JM_GameStates m_lastState;
    JM_BaseStateMachine* m_currentState;
    JM_WorldGUIInterface m_interface;

    void changeState();

public:
    JM_Game(SDL_Surface* screen);

    void handleInput();
    void update(int dTime);
    void render();

    ~JM_Game();
};

}
#endif

