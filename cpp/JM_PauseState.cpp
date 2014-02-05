#include "JM_PauseState.h"
#include "JM_GUIButtonElement.h"

namespace JM_Library
{

JM_PauseState::JM_PauseState(JM_World& world)
    : m_world(world)
{
    m_type = STATE_PAUSE;
    m_nextState = STATE_NULL;
}

void JM_PauseState::initGUI(SDL_Surface* screen)
{
    JM_GUI gui;
    gui.setScreen(screen);
    setGUI(gui);

    JM_GUIButtonElement* quitbutton = new JM_GUIButtonElement(BUTTONELEMENTTYPE_QUIT);
    quitbutton->setGFX("GFX/mainmenubutton.png");
    quitbutton->setPosition(320 - (192 / 2), 240 - (39 / 2), 192, 39);

    getGUI().addElement(quitbutton);
}

void JM_PauseState::handleInput()
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

void JM_PauseState::update(int dTime)
{
    getGUI().update(dTime);
}

void JM_PauseState::render()
{
    m_world.render();
    getGUI().render();
}

void JM_PauseState::activateButton(JM_GUIElementTypes type)
{
    if(type != ELEMENTTYPE_NULL)
    {
        switch(type)
        {
        case BUTTONELEMENTTYPE_QUIT: setNextState(STATE_MAINMENU); break;
        default: break;
        }
    }
}

JM_PauseState::~JM_PauseState()
{
}

}