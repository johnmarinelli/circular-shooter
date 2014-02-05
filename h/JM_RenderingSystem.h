/*
* system to manage rendercomponents
*/

#ifndef _JM_RENDERINGSYSTEM_H
#define _JM_RENDERINGSYSTEM_H

#include "JM_BaseSystem.h"
#include "JM_RenderComponent.h"

namespace JM_Library{

class JM_RenderingSystem
    : public JM_BaseSystem
{
private:
    typedef std::vector<JM_RenderComponent*> RenderComponentVector;
    typedef RenderComponentVector::iterator RenderComponentIterator;

    RenderComponentVector m_renderComponents;
    SDL_Surface* m_screen;

public:
    JM_RenderingSystem();

    void setScreen(SDL_Surface* screen);

    void update(int dTime);
    JM_RenderComponent* createComponent(JM_ComponentType type);
    void addComponent(JM_BaseComponent* component);
    void removeComponent(int id);
    
    void clearSystem();

    ~JM_RenderingSystem();
};

}

#endif
