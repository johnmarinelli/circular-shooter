#include "JM_PlayerStats.h"

namespace JM_Library
{

JM_PlayerStats::JM_PlayerStats(int health, unsigned int damage, unsigned int bullets, unsigned int points)
    : m_health(health), m_damage(damage), m_bullets(bullets), m_points(points)
{
}

void JM_PlayerStats::reset()
{
    m_health = 1;
    m_damage = 1;
    m_bullets = 10;
    m_points = 0;
}

JM_PlayerStats::~JM_PlayerStats()
{
}

}