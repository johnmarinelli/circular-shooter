/*
* game over state when lives < 1 || enemies escaped > 14.  next state: main menu.
*/

#ifndef _JM_GAMEOVERSTATE_H
#define _JM_GAMEOVERSTATE_H

#include "JM_BaseStateMachine.h"

namespace JM_Library
{

class JM_GameOverState :
    public JM_BaseStateMachine
{
private:
    SDL_Event m_event;
    SDL_Surface* m_title;
    SDL_Surface* m_screen;

public:
    JM_GameOverState();
    
    void initGUI(SDL_Surface* screen);

    void handleInput();
    void update(int dTime);
    void render();

    void activateButton(JM_GUIElementTypes type);

    ~JM_GameOverState();
};

}

#endif