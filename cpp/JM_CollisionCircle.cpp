#include "JM_CollisionCircle.h"

namespace JM_Library
{

JM_CollisionCircle::JM_CollisionCircle()
    : m_xPosition(0), m_yPosition(0), m_radius(0)
{
}

void JM_CollisionCircle::initialize(float x, float y, float radius)
{
    m_xPosition = x;
    m_yPosition = y;
    m_radius = radius;
}

void JM_CollisionCircle::reset()
{
    m_xPosition = 0;
    m_yPosition = 0;
    m_radius = 0;
}

JM_CollisionCircle::~JM_CollisionCircle()
{
}

}