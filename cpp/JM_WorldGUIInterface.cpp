#include "JM_WorldGUIInterface.h"
#include <sstream>

namespace JM_Library
{

JM_WorldGUIInterface::JM_WorldGUIInterface(JM_World& world)
    : m_world(&world)
{
}

void JM_WorldGUIInterface::update(int dTime)
{ 
    if(m_world && m_gui){
        std::string count = "";

        if(m_gui->getElement(ELEMENTTYPE_BULLET)){
            count = "Bullets: " + numberToString(m_world->getData<int>("bulletcount"));
            m_gui->getElement(ELEMENTTYPE_BULLET)->setText(count);
        }

        if(m_gui->getElement(ELEMENTTYPE_LIVES)){
            count = "Health: " + numberToString(m_world->getData<int>("healthcount"));
            m_gui->getElement(ELEMENTTYPE_LIVES)->setText(count);
        }

        if(m_gui->getElement(ELEMENTTYPE_POINTS)){
            count = "Points: " + numberToString(m_world->getData<int>("pointscount"));
            m_gui->getElement(ELEMENTTYPE_POINTS)->setText(count);
        }

        if(m_gui->getElement(ELEMENTTYPE_LEVEL)){
            count = "Level: " + numberToString(m_world->getData<int>("levelcount"));
            m_gui->getElement(ELEMENTTYPE_LEVEL)->setText(count);
        }
    }

    else
        printf("World or GUI is null; WorldGUIInterface::update():\n");
}

void JM_WorldGUIInterface::setGUI(JM_GUI& gui)
{ 
    m_gui = &gui;
}

JM_WorldGUIInterface::~JM_WorldGUIInterface()
{
}

}