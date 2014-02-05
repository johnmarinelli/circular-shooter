#include "JM_RenderingSystem.h"

namespace JM_Library
{

JM_RenderingSystem::JM_RenderingSystem()
    : m_screen(NULL)
{
    m_systemType = SYSTEM_TYPE_RENDER;
}

void JM_RenderingSystem::setScreen(SDL_Surface* screen)
{
    m_screen = screen;
}

void JM_RenderingSystem::update(int dTime)
{
    //red boxes for design
    SDL_Rect outerredbox = { 245, 140, 200, 200 };
    SDL_FillRect(m_screen, &outerredbox, SDL_MapRGB(m_screen->format, 0xFF, 0x99, 0x00));
    SDL_Rect innerredbox = { 295, 190, 100, 100 };
    SDL_FillRect(m_screen, &innerredbox, SDL_MapRGB(m_screen->format, 0xFF, 0x00, 0x00));

    RenderComponentIterator itr = m_renderComponents.begin();

    while(itr != m_renderComponents.end()){
        (*itr)->render(m_screen);
        ++itr;
    } 
}

JM_RenderComponent* JM_RenderingSystem::createComponent(JM_ComponentType type)
{
    if(type == TYPE_RENDER){
        JM_RenderComponent* rc = new JM_RenderComponent();
        addComponent(rc);
        return rc;
    }

    else
        return NULL;
}

void JM_RenderingSystem::addComponent(JM_BaseComponent* component)
{
    //add component to the systems' registry, 
    //register this system as components' parent
    m_renderComponents.push_back(static_cast<JM_RenderComponent*>(component));
    m_renderComponents.back()->setParentSystem(this);
}

void JM_RenderingSystem::removeComponent(int id)
{
    RenderComponentIterator itr = m_renderComponents.begin();

    while(itr != m_renderComponents.end())
    {
        if((*itr)->getID() == id){
            safeDelete((*itr));
            //HAVE EACH SYSTEM HAVE A POOL OF COMPONENTS
            //(*itr)->reset();
            itr = m_renderComponents.erase(itr);
        }

        else
            ++itr;
    }

    /*RenderComponentIterator itr = m_renderComponents.begin();

    while((*itr)->getID() != id){
        ++itr;
    } 

    //need to remove from m_owner as well, + delete & set pointer to NULL
    //look in JM_BaseComponent::unregister()
    if(itr != m_renderComponents.end()){
        (*itr)->setParentSystem(NULL);
        safeDelete(*itr);
        m_renderComponents.erase(itr);
    }*/
}

void JM_RenderingSystem::clearSystem()
{
    RenderComponentIterator itr = m_renderComponents.begin();

    while(itr != m_renderComponents.end())
    {
        safeDelete((*itr));
        itr = m_renderComponents.erase(itr);
    }
}

JM_RenderingSystem::~JM_RenderingSystem()
{
    std::for_each(m_renderComponents.begin(), m_renderComponents.end(), JM_DeleteObject());
}

}