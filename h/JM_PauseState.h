/*
* pause state while in game. next state: playing state
*/

#ifndef _JM_PAUSESTATE_H
#define _JM_PAUSESTATE_H

#include "JM_BaseStateMachine.h"
#include "JM_World.h"
#include "JM_GUI.h"

namespace JM_Library
{

class JM_PauseState :
    public JM_BaseStateMachine
{
private:
    JM_World& m_world;

    SDL_Event m_event;

public:
    JM_PauseState(JM_World& world);

    void initGUI(SDL_Surface* screen);

    void handleInput();
    void update(int dTime);
    void render();

    void activateButton(JM_GUIElementTypes type);

    ~JM_PauseState();
};

}

#endif