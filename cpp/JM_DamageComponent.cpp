#include "JM_DamageComponent.h"

namespace JM_Library
{

JM_DamageComponent::JM_DamageComponent()
    : m_damage(0)
{
    m_type = TYPE_DAMAGE;
}

void JM_DamageComponent::reset()
{
    m_damage = 0;
}

JM_DamageComponent::~JM_DamageComponent()
{
}

}