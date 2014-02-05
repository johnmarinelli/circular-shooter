#include "JM_HealthSystem.h"

namespace JM_Library
{

JM_HealthSystem::JM_HealthSystem()
{
    m_systemType = SYSTEM_TYPE_HEALTH;
}

void JM_HealthSystem::addComponent(JM_HealthComponent* component)
{
    component->setParentSystem(this);
    m_components.push_back(component);
}

void JM_HealthSystem::update(int dTime)
{
    HealthComponentIterator itr = m_components.begin();
    
    while(itr != m_components.end()){
        (*itr)->update(dTime);
        ++itr;
    }
}

void JM_HealthSystem::removeComponent(int id)
{
    HealthComponentIterator itr = m_components.begin();

    while(itr != m_components.end())
    {
        if((*itr)->getID() == id){
            safeDelete((*itr));
            //HAVE EACH SYSTEM HAVE A POOL OF COMPONENTS
            //(*itr)->reset();
            itr = m_components.erase(itr);
        }

        else
            ++itr;
    }
}

JM_HealthComponent* JM_HealthSystem::createComponent(JM_ComponentType type)
{
    if(type == TYPE_HEALTH){
        JM_HealthComponent* hc = new JM_HealthComponent();
        addComponent(hc);
        return hc;
    }

    else
        return NULL;
}

void JM_HealthSystem::clearSystem()
{
    HealthComponentIterator itr = m_components.begin();

    while(itr != m_components.end())
    {
        safeDelete((*itr));
        itr = m_components.erase(itr);
    }
}

JM_HealthSystem::~JM_HealthSystem()
{
}

}