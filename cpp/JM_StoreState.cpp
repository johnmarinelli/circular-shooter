#include "JM_StoreState.h"
#include <sstream>

namespace JM_Library
{

JM_StoreState::JM_StoreState(JM_World& world, JM_PlayerStats& stats)
    : m_world(world), m_playerStats(stats)
{
    m_type = STATE_STORE;
    m_nextState = STATE_NULL;
}

void JM_StoreState::initGUI(SDL_Surface* screen)
{
    JM_GUI gui;
    gui.setScreen(screen);
    setGUI(gui);

    JM_GUIButtonElement* buybulletsbutton = new JM_GUIButtonElement(BUTTONELEMENTTYPE_BUYBULLETS);
    buybulletsbutton->setGFX("GFX/buybulletsbutton.png");
    buybulletsbutton->setPosition(320 - (192 / 2), 240 - (39 / 2), 192, 39);

    JM_GUIButtonElement* buylifebutton = new JM_GUIButtonElement(BUTTONELEMENTTYPE_BUYLIFE);
    buylifebutton->setGFX("GFX/buylifebutton.png");
    buylifebutton->setPosition(320 - (192 / 2), buybulletsbutton->getBox().y + 50, 192, 39);

    JM_GUIButtonElement* upgradebulletsbutton = new JM_GUIButtonElement(BUTTONELEMENTTYPE_UPGRADEBULLETS);
    upgradebulletsbutton->setGFX("GFX/upgradebulletsbutton.png");
    upgradebulletsbutton->setPosition(320 - (192 / 2), buylifebutton->getBox().y + 50, 192, 39);

    JM_GUIButtonElement* continuebutton = new JM_GUIButtonElement(BUTTONELEMENTTYPE_CONTINUE);
    continuebutton->setGFX("GFX/continuebutton.png");    
    continuebutton->setPosition(320 - (192 / 2), upgradebulletsbutton->getBox().y + 50, 192, 39);
    
    JM_GUIElement* pointselement = new JM_GUIElement();
    pointselement->m_type = ELEMENTTYPE_POINTS;
    pointselement->setPosition(0, 40, 0, 0);

    JM_GUIElement* errorelement = new JM_GUIElement();
    errorelement->m_type = ELEMENTTYPE_ERROR;
    errorelement->setPosition(320 - (192 / 2), 450, 0, 0);

    getGUI().addElement(buybulletsbutton);
    getGUI().addElement(buylifebutton);
    getGUI().addElement(upgradebulletsbutton);
    getGUI().addElement(continuebutton);
    getGUI().addElement(pointselement);
    getGUI().addElement(errorelement);
}

void JM_StoreState::handleInput()
{
    while(SDL_PollEvent(&m_event))
    {
        if(m_event.type ==  SDL_MOUSEBUTTONDOWN){
            if(m_event.button.button == SDL_BUTTON_LEFT){
                activateButton(getGUI().handleClick(m_event.button.x, m_event.button.y));
            }
        }
        
        else if(m_event.type == SDL_QUIT){
            running = false;
        }
    }
}

void JM_StoreState::update(int dTime)
{
    std::string pointscount = numberToString(m_playerStats.m_points);
    getGUI().getElement(ELEMENTTYPE_POINTS)->setText(pointscount);
    getGUI().update(dTime);
}

void JM_StoreState::render()
{
    getGUI().render();
}

void JM_StoreState::activateButton(JM_GUIElementTypes type)
{
    if(type != ELEMENTTYPE_NULL){
        int ptsreq = 0;

        switch(type){
        case BUTTONELEMENTTYPE_BUYBULLETS:ptsreq = 1; break;
        case BUTTONELEMENTTYPE_BUYLIFE: ptsreq = 10; break;
        case BUTTONELEMENTTYPE_UPGRADEBULLETS: ptsreq = 25; break;
        case BUTTONELEMENTTYPE_CONTINUE: ptsreq = 0; break;
        default: break;
        }

        buy(type, ptsreq);
    }
}

void JM_StoreState::buy(JM_GUIElementTypes type, int ptsreq)
{
    if((signed)m_playerStats.m_points > ptsreq - 1){
        switch(type){
        case BUTTONELEMENTTYPE_BUYBULLETS: m_playerStats.m_bullets += 2; break;
        case BUTTONELEMENTTYPE_BUYLIFE: m_playerStats.m_health++; break;
        case BUTTONELEMENTTYPE_UPGRADEBULLETS: m_playerStats.m_damage++; break;
        case BUTTONELEMENTTYPE_CONTINUE: m_world.reset(); setNextState(STATE_PLAYING); break;
        }

        m_playerStats.m_points -= ptsreq;
    }
    
    else
        getGUI().getElement(ELEMENTTYPE_ERROR)->setText("COME BACK WITH MORE MONEY, ASS");
}

JM_StoreState::~JM_StoreState()
{
}

}