/*
* class used so that world & gui can communicate in playing state.
*/

#ifndef _JM_WORLDGUIINTERFACE_H
#define _JM_WORLDGUIINTERFACE_H

#include "JM_Interface.h"
#include "JM_World.h"
#include "JM_GUI.h"

namespace JM_Library
{

class JM_WorldGUIInterface :
    public JM_Interface
{
private:
    JM_World* m_world;
    JM_GUI* m_gui;

public:
    JM_WorldGUIInterface(JM_World& world);
    
    void update(int dTime);
    void setGUI(JM_GUI& gui);

    ~JM_WorldGUIInterface();
};

}

#endif