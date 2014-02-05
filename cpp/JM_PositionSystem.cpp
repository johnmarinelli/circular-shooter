#include "JM_PositionSystem.h"

namespace JM_Library
{
JM_PositionSystem::JM_PositionSystem()
{
    m_systemType = SYSTEM_TYPE_POSITION;
}

void JM_PositionSystem::update(int dTime)
{
    SystemComponentIterator itr = m_components.begin();
    
    while(itr != m_components.end()){
        (*itr)->update(dTime);
        ++itr;
    }

    m_collisionSystem.update(dTime);
}

JM_PositionComponent* JM_PositionSystem::createComponent(JM_ComponentType type, JM_OwnerType ownertype)
{
    if(type == TYPE_POSITION){
        JM_PositionComponent* pc = new JM_PositionComponent();
        pc->m_ownerType = ownertype;
        addComponent(pc, ownertype);
        return pc;
    }

    else
        return NULL;
}

void JM_PositionSystem::addComponent(JM_BaseComponent* component, JM_OwnerType ownertype)
{
    //add component to the systems' registry, 
    //register this system as components' parent
    component->setParentSystem(this);
    m_components.push_back(component);

    m_collisionSystem.addComponent(component, ownertype);
}

void JM_PositionSystem::removeComponent(int id)
{
    m_collisionSystem.removeComponent(id);

    SystemComponentIterator itr = m_components.begin();

    while(itr != m_components.end())
    {
        if((*itr)->getID() == id){
            safeDelete((*itr));
            //HAVE EACH SYSTEM HAVE A POOL OF COMPONENTS
            //(*itr)->reset();
            itr = m_components.erase(itr);
            return;
        }

        else
            ++itr;
    }
}

const int JM_PositionSystem::getPlayerHits()
{
    if(m_collisionSystem.m_playerHitsDirty){
        m_collisionSystem.m_playerHitsDirty = false; 
        return m_collisionSystem.m_playerHits; 
    }

    else return 0;
}

const int JM_PositionSystem::getEnemiesEscaped()
{
    return m_collisionSystem.m_enemiesEscaped;
}

void JM_PositionSystem::clearSystem()
{
    SystemComponentIterator itr = m_components.begin();

    while(itr != m_components.end()){
        safeDelete((*itr));
        itr = m_components.erase(itr);
    }

    m_collisionSystem.clearSystem();
}

JM_PositionSystem::~JM_PositionSystem()
{
}

}