#include "JM_PositionComponent.h"
#include <math.h>

namespace JM_Library{

JM_PositionComponent::JM_PositionComponent()
    : m_xVelocity(0.f), m_yVelocity(0.f), m_ownerType(OWNERTYPE_NULL)
{
    m_type = TYPE_POSITION;

    m_collisionBox.x = 0.f; 
    m_collisionBox.y = 0.f;
    m_collisionBox.w = 0.f;
    m_collisionBox.h = 0.f;
}

void JM_PositionComponent::setCollisionBox(const SDL_Rect& box)
{
    m_collisionBox.x = box.x;
    m_collisionBox.y = box.y;
    m_collisionBox.w = box.w;
    m_collisionBox.h = box.h;
}

void JM_PositionComponent::update(int dTime)
{ 
    float delta = dTime / 1000.f;

    m_collisionBox.x += m_xVelocity * delta;
    m_collisionBox.y += m_yVelocity * delta;
}

void JM_PositionComponent::reset()
{
    m_collisionBox.x = 0.f;
    m_collisionBox.y = 0.f;
    m_collisionBox.w = 0.f;
    m_collisionBox.h = 0.f;

    m_xVelocity = 0;
    m_yVelocity = 0;

    m_ownerType = OWNERTYPE_NULL;
}

JM_PositionComponent::~JM_PositionComponent()
{
}

};