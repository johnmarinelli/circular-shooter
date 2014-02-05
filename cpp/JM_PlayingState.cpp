#include "JM_PlayingState.h"
#include "JM_GUIElement.h"

namespace JM_Library
{

JM_PlayingState::JM_PlayingState(JM_World& world, JM_PlayerStats& stats)
    : m_world(world), m_playerStats(stats)
{
    m_type = STATE_PLAYING;
    m_nextState = STATE_NULL;
}

void JM_PlayingState::initGUI(SDL_Surface* screen)
{
    JM_GUI gui;
    gui.setScreen(screen);
    setGUI(gui);

    JM_GUIElement* bulletelement = new JM_GUIElement();
    bulletelement->m_type = ELEMENTTYPE_BULLET;

    JM_GUIElement* liveselement = new JM_GUIElement();
    liveselement->m_type = ELEMENTTYPE_LIVES;
    liveselement->setPosition(0, 40, 0, 0);

    JM_GUIElement* pointselement = new JM_GUIElement();
    pointselement->m_type = ELEMENTTYPE_POINTS;
    pointselement->setPosition(0, 80, 0, 0);

    JM_GUIElement* levelelement = new JM_GUIElement();
    levelelement->m_type = ELEMENTTYPE_LEVEL;
    levelelement->setPosition(0, 120, 0, 0);

    getGUI().addElement(bulletelement);
    getGUI().addElement(liveselement);
    getGUI().addElement(pointselement);
    getGUI().addElement(levelelement);
}

void JM_PlayingState::handleInput()
{
    m_world.handleInput();
}

void JM_PlayingState::update(int dTime)
{
    m_world.update(dTime);
    getGUI().update(dTime);
    setNextState(m_world.getNextState());
}

void JM_PlayingState::render()
{
    m_world.render();
    getGUI().render();
}

JM_PlayingState::~JM_PlayingState()
{
    //m_gui.erase
}

}