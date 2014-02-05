#include "JM_DamageSystem.h"

namespace JM_Library
{

JM_DamageSystem::JM_DamageSystem()
{
}

void JM_DamageSystem::update(int dTime)
{
}

void JM_DamageSystem::addComponent(JM_DamageComponent* component)
{
    component->setParentSystem(this);
    m_components.push_back(component);
}

JM_DamageComponent* JM_DamageSystem::createComponent(JM_ComponentType type)
{
    if(type == TYPE_DAMAGE){
        JM_DamageComponent* dc = new JM_DamageComponent();
        addComponent(dc);
        return dc;
    }

    else
        return NULL;
}

void JM_DamageSystem::removeComponent(int id)
{
    DamageComponentIterator itr = m_components.begin();

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

void JM_DamageSystem::clearSystem()
{
    DamageComponentIterator itr = m_components.begin();

    while(itr != m_components.end())
    {
        safeDelete((*itr));
        itr = m_components.erase(itr);
    }
}

JM_DamageSystem::~JM_DamageSystem()
{
}

}
