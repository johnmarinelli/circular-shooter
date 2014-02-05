/*
* Playing state of the game.  Handles all the logic/rendering of world and the communication between world & GUI.
*/

#ifndef _JM_PLAYINGSTATE_H
#define _JM_PLAYINGSTATE_H

#include "JM_BaseStateMachine.h"
#include "JM_World.h"
#include "JM_GUI.h"

namespace JM_Library
{

class JM_PlayingState :
    public JM_BaseStateMachine
{
private:
    JM_World& m_world;

    JM_PlayerStats& m_playerStats;

public:
    JM_PlayingState(JM_World& world, JM_PlayerStats& stats);

    void initGUI(SDL_Surface* screen);

    void handleInput();
    void update(int dTime);
    void render();

    ~JM_PlayingState();
};

}

#endif