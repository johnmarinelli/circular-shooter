/*
* class for data that's persistent across states and relative to player
*/

#ifndef _JM_PLAYERSTATS_H
#define _JM_PLAYERSTATS_H

namespace JM_Library
{

struct JM_PlayerStats
{
    int m_health;
    unsigned int m_damage;
    unsigned int m_bullets;
    unsigned int m_points;

    void reset();

    JM_PlayerStats(int health = 1, unsigned int damage = 1, unsigned int bullets = 10, unsigned int points = 0);
    ~JM_PlayerStats();
};

}
#endif
