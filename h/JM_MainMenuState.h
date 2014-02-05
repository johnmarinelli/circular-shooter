/*
* main menu state for game. next state: playing state
*/

#ifndef _JM_MAINMENUSTATE_H
#define _JM_MAINMENUSTATE_H

#include "JM_BaseStateMachine.h"

namespace JM_Library
{

class JM_MainMenuState :
    public JM_BaseStateMachine
{
private:
    static const int MILLISECONDS_FOR_MESSAGE = 500;

    SDL_Surface* m_title;
    SDL_Surface* m_screen;

    SDL_Event m_event;

    int m_secondsInterval;
    bool m_showMessage;

public:
    JM_MainMenuState();

    void initGUI(SDL_Surface* screen);

    void handleInput();
    void update(int dTime);
    void render();

    ~JM_MainMenuState();
};

}

#endif