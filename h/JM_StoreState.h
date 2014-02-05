/*
* state to manage buying items for points.  next states: playing state or main menu
*/

#ifndef _JM_STORESTATE_H
#define _JM_STORESTATE_H

#include "JM_BaseStateMachine.h"
#include "JM_World.h"
#include "JM_PlayerStats.h"

namespace JM_Library
{

class JM_StoreState :
    public JM_BaseStateMachine
{
private:
    JM_World& m_world;
    SDL_Event m_event;

    JM_PlayerStats& m_playerStats;

    void buy(JM_GUIElementTypes, int ptsreq);

public:
    JM_StoreState(JM_World& world, JM_PlayerStats& stats);

    void initGUI(SDL_Surface* screen);

    void handleInput();
    void update(int dTime);
    void render();

    void activateButton(JM_GUIElementTypes type);

    ~JM_StoreState();
};

}

#endif