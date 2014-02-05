#include "JM_BaseStateMachine.h"

namespace JM_Library
{

JM_GUI& JM_BaseStateMachine::getGUI()
{
    return m_gui;
}

void JM_BaseStateMachine::setGUI(JM_GUI gui)
{
    m_gui = gui;
}

void JM_BaseStateMachine::setNextState(JM_GameStates nextState)
{
    m_nextState = nextState;
}

JM_BaseStateMachine::~JM_BaseStateMachine()
{
}

}