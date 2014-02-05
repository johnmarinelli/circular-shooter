#include "JM_MainMenuState.h"

namespace JM_Library
{
    
JM_MainMenuState::JM_MainMenuState()
  : m_title(loadImage("GFX/mainmenutitle.png")), m_screen(SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE)), m_secondsInterval(0), m_showMessage(true)
{
    m_type = STATE_MAINMENU;
    m_nextState = STATE_NULL;
}

void JM_MainMenuState::initGUI(SDL_Surface* screen)
{
    JM_GUI gui;
    gui.setScreen(screen);
    setGUI(gui);

    JM_GUIElement* gamestartelement = new JM_GUIElement();
    gamestartelement->m_type = ELEMENTTYPE_START;
    gamestartelement->setPosition(250, 400, 0, 0);
    getGUI().addElement(gamestartelement);

    gamestartelement->setText("Press 'n' to start...");
}

void JM_MainMenuState::handleInput()
{
    while(SDL_PollEvent(&m_event)){
        if(m_event.type == SDL_KEYDOWN){
            if(m_event.key.keysym.sym == SDLK_n){
                setNextState(STATE_PLAYING);
            }
        }
        
        else if(m_event.type == SDL_QUIT){
            running = false;
        }
    }
}

void JM_MainMenuState::update(int dTime)
{
    m_secondsInterval += dTime;
    if(m_secondsInterval > MILLISECONDS_FOR_MESSAGE){
        m_showMessage = !m_showMessage;
        m_secondsInterval = 0;
    }
}

void JM_MainMenuState::render()
{
    applySurface(55, 150, m_title, m_screen);
    if(m_showMessage) getGUI().render();
    //SDL_Flip(m_screen);
}

JM_MainMenuState::~JM_MainMenuState()
{
    SDL_FreeSurface(m_title);
    SDL_FreeSurface(m_screen);
}

}