#include "JM_GameOverState.h"

namespace JM_Library
{

JM_GameOverState::JM_GameOverState()
    : m_title(loadImage("GFX/gameovertitle.png"))
{
    m_type = STATE_GAMEOVER;
    m_nextState = STATE_NULL;
}

void JM_GameOverState::initGUI(SDL_Surface* screen)
{
    m_screen = screen;

    JM_GUI gui;
    gui.setScreen(screen);
    setGUI(gui);

    JM_GUIButtonElement* quitbutton = new JM_GUIButtonElement(BUTTONELEMENTTYPE_QUIT);
    quitbutton->setGFX("GFX/mainmenubutton.png");
    quitbutton->setPosition(320 - (192 / 2), 300, 192, 39);

    getGUI().addElement(quitbutton);
}

void JM_GameOverState::handleInput()
{
    while(SDL_PollEvent(&m_event))
    {        
        if(m_event.type ==  SDL_MOUSEBUTTONDOWN){
            if(m_event.button.button == SDL_BUTTON_LEFT){
                activateButton(getGUI().handleClick(m_event.button.x, m_event.button.y));
            }
        }

        else if(m_event.type == SDL_KEYDOWN){
            if(m_event.key.keysym.sym == SDLK_p){
                setNextState(STATE_PLAYING);
            }
        }
    }
}

void JM_GameOverState::update(int dTime)
{
    getGUI().update(dTime);
}

void JM_GameOverState::render()
{
    applySurface(137, 50, m_title, m_screen);
    getGUI().render();
}

void JM_GameOverState::activateButton(JM_GUIElementTypes type)
{
    if(type != ELEMENTTYPE_NULL){
        switch(type){
        case BUTTONELEMENTTYPE_QUIT: setNextState(STATE_MAINMENU); break;
        default: break;
        }
    }
}

JM_GameOverState::~JM_GameOverState()
{
    SDL_FreeSurface(m_title);
}

}