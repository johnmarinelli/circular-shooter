#include "JM_InputSystem.h"

namespace JM_Library
{

JM_InputSystem::JM_InputSystem()
{
    m_systemType = SYSTEM_TYPE_INPUT;
}

void JM_InputSystem::update(int dTime)
{
    InputComponentIterator itr = m_inputComponents.begin();

    while(SDL_PollEvent(&m_event))
    {
        while(itr != m_inputComponents.end()){
          (*itr)->update(m_event);
           ++itr;
        }
    }
}

JM_InputComponent* JM_InputSystem::createComponent(JM_ComponentType type)
{
    if(type == TYPE_INPUT){
        JM_InputComponent* ic = new JM_InputComponent();
        addComponent(ic);
        return ic;
    }

    else
        return NULL;
}

void JM_InputSystem::addComponent(JM_BaseComponent* component)
{
    m_inputComponents.push_back(static_cast<JM_InputComponent*>(component));
    m_inputComponents.back()->setParentSystem(this);
}

void JM_InputSystem::removeComponent(int id)
{
    InputComponentIterator itr = m_inputComponents.begin();

    while((*itr)->getID() != id){
        ++itr;
    } 

    if(itr != m_inputComponents.end()){
        (*itr)->setParentSystem(NULL);
        m_inputComponents.erase(itr);
    }
}

void JM_InputSystem::clearSystem()
{
    InputComponentIterator itr = m_inputComponents.begin();

    while(itr != m_inputComponents.end())
    {
        safeDelete((*itr));
        itr = m_inputComponents.erase(itr);
    }
}

JM_InputSystem::~JM_InputSystem()
{
    std::for_each(m_inputComponents.begin(), m_inputComponents.end(), JM_DeleteObject());
}

}