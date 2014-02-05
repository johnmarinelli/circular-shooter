/*
* This class is the base gamestate machine for the game.
* handles switching between gamestates.
*/

#ifndef _JM_BASESTATEMACHINE_H
#define _JM_BASESTATEMACHINE_H

#include "JM_Utilities.h"
#include "JM_GameStates.h"
#include "JM_GUI.h"

namespace JM_Library
{

class JM_BaseStateMachine
{
private:
    JM_GUI m_gui;

public:
    JM_GameStates m_type;
    JM_GameStates m_nextState;

    void setNextState(JM_GameStates nextState);

    JM_GUI& getGUI();
    void setGUI(JM_GUI gui);

    virtual void initGUI(SDL_Surface* screen) = 0;

    virtual void handleInput() = 0;
    virtual void update(int dTime) = 0;
    virtual void render() = 0;

    virtual ~JM_BaseStateMachine();
};

}

#endif