#include "JM_Game.h"
#include "JM_MainMenuState.h"
#include "JM_PlayingState.h"
#include "JM_PauseState.h"
#include "JM_StoreState.h"
#include "JM_GameOverState.h"

namespace JM_Library
{

void JM_Game::changeState()
{
    m_lastState = m_currentState->m_type;

    if(m_currentState->m_nextState != STATE_NULL){
        switch(m_currentState->m_nextState){
        case STATE_MAINMENU: m_currentState = new JM_MainMenuState; break;
        case STATE_PLAYING: if(m_lastState == STATE_MAINMENU) m_world.reset(true); 
            m_currentState = new JM_PlayingState(m_world, m_playerStats); break;
        case STATE_PAUSE: m_currentState = new JM_PauseState(m_world); break;
        case STATE_STORE: m_currentState = new JM_StoreState(m_world, m_playerStats); break;
        case STATE_GAMEOVER: m_currentState = new JM_GameOverState(); break;

        default: break;
        };

        m_currentState->initGUI(m_screen);
        m_interface.setGUI(m_currentState->getGUI());
    }
}

JM_Game::JM_Game(SDL_Surface* screen)
    : m_screen(screen), m_currentState(new JM_MainMenuState), m_lastState(STATE_NULL), m_level(0), m_world(screen, m_playerStats, m_level), m_interface(m_world)
{
    m_interface.setGUI(m_currentState->getGUI());
    m_currentState->initGUI(m_screen);
}

void JM_Game::handleInput()
{
    m_currentState->handleInput();
}

void JM_Game::update(int dTime)
{
    m_currentState->update(dTime);
    m_interface.update(dTime);
    changeState();
}

void JM_Game::render()
{
    //if it's gameover, fill black. otherwise, fill white.
    if(m_currentState->m_type != STATE_GAMEOVER && m_currentState->m_type != STATE_MAINMENU) 
        SDL_FillRect(m_screen, &m_screen->clip_rect, SDL_MapRGB(m_screen->format, 0xF0, 0xF0, 0xF0));

    else SDL_FillRect(m_screen, &m_screen->clip_rect, SDL_MapRGB(m_screen->format, 0xFF, 0xFF, 0xFF));

    m_currentState->render();
    
    SDL_Flip(m_screen);
}

JM_Game::~JM_Game()
{
}

}