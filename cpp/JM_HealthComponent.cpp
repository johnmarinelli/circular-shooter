#include "JM_HealthComponent.h"

namespace JM_Library
{

JM_HealthComponent::JM_HealthComponent() 
    : m_health(0)
{
    m_type = TYPE_HEALTH;
}

void JM_HealthComponent::update(int dTime)
{
    if(m_health < 1){
        m_owner->m_isActive = false;
    }
}

void JM_HealthComponent::reset()
{
    m_health = 0;
}

JM_HealthComponent::~JM_HealthComponent()
{
}

}