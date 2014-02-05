#include "JM_PlayerPositionComponent.h"

namespace JM_Library
{

JM_PlayerPositionComponent::JM_PlayerPositionComponent()
    : m_angle(0), m_velocity(0), m_origin(0, 0), m_originRadius(0)
{
    m_type = TYPE_POSITION;
    m_ownerType = OWNERTYPE_PLAYER;

    m_collisionBox.x = 0;
    m_collisionBox.y = 0;
    m_collisionBox.w = 0;
    m_collisionBox.h = 0;
}

void JM_PlayerPositionComponent::initialize(float originx, float originy, float xPos, float yPos, float radius)
{
    m_angle = 0;
    m_velocity = 0;
    m_origin.x = originx - radius;
    m_origin.y = originy - radius;

    m_originRadius = 220;

    //m_collisionCircle.m_xPosition = xPos - radius;
    //m_collisionCircle.m_yPosition = yPos - radius;
    
    m_collisionCircle.m_xPosition = m_origin.x + (std::cos(m_angle) * m_originRadius);
    m_collisionCircle.m_yPosition = m_origin.y + (std::sin(m_angle) * m_originRadius);
    m_collisionCircle.m_radius = radius;

    //for rendering component
    m_collisionBox.x = xPos - radius;
    m_collisionBox.y = yPos - radius;
}

void JM_PlayerPositionComponent::update(int dTime)
{
    float time = dTime / 1000.f;

    m_collisionCircle.m_xPosition = m_origin.x + (std::cos(m_angle) * m_originRadius);
    m_collisionCircle.m_yPosition = m_origin.y + (std::sin(m_angle) * m_originRadius);

    m_angle += m_velocity;

    if(m_angle > 360){
        m_angle = 0;
    }

    //for rendering
    m_collisionBox.x = (int)m_collisionCircle.m_xPosition;
    m_collisionBox.y = (int)m_collisionCircle.m_yPosition;
}

void JM_PlayerPositionComponent::reset()
{
    m_collisionBox.x = 0;
    m_collisionBox.y = 0;
    m_collisionBox.w = 0;
    m_collisionBox.h = 0;

    m_collisionCircle.reset();
    m_angle = 0;
    m_xVelocity = 0;
    m_yVelocity = 0;
    m_origin.x = 0;
    m_origin.y = 0;

    m_originRadius = 0;
}

JM_CollisionCircle& JM_PlayerPositionComponent::getCircle()
{
    return m_collisionCircle;
}

JM_PlayerPositionComponent::~JM_PlayerPositionComponent()
{
}

}