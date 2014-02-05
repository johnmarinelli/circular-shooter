/*
* system to handle input component.
*/
#ifndef _JM_INPUTSYSTEM_H
#define _JM_INPUTSYSTEM_H

#include "JM_BaseSystem.h"
#include "JM_InputComponent.h"

namespace JM_Library
{

class JM_InputSystem :
    public JM_BaseSystem
{
private:
    typedef std::vector<JM_InputComponent*> InputComponentVector;
    typedef InputComponentVector::iterator InputComponentIterator;

    InputComponentVector m_inputComponents;
    SDL_Event m_event;

public:
    JM_InputSystem();

    void update(int dTime);
    JM_InputComponent* createComponent(JM_ComponentType type);
    void addComponent(JM_BaseComponent* component);
    void removeComponent(int id);
    
    void clearSystem();

    ~JM_InputSystem();
};

}
#endif