/*
* class to spawn enemies.
* there can never be more than 10 enemies on the screen.  inactive enemies will be reused instead 
* of constantly allocating new memory
*/

#ifndef _JM_ENEMYFACTORY_H
#define _JM_ENEMYFACTORY_H

#include "JM_Entity.h"
#include <stack>
#include "JM_RenderingSystem.h"
#include "JM_PositionSystem.h"
#include "JM_HealthSystem.h"
#include "JM_DamageSystem.h"

const int MAX_ENEMIES = 10;
const int SPAWN_AREA_SIDE = 20;
const int ENEMY_SIDE = 20;
const float ENEMY_VELOCITY_FLOOR = 40.f;

//after 30 levels, this will double the original velocity
const float ENEMY_VELOCITY_INC = 1.3300000f;

namespace JM_Library
{

class JM_EnemyFactory
{
private:
    typedef std::stack<JM_Entity*> EntityStack;
    
    EntityStack m_entityPool;

    int m_numberOfEnemies;
    int m_activeEnemies;
    int m_inactiveEnemies;

public:
    JM_EnemyFactory();

    JM_Entity* spawnEnemy(JM_RenderingSystem& rendersystem, JM_PositionSystem& positionsystem, JM_HealthSystem& healthsystem, JM_DamageSystem& damagesystem, int level);
    void returnEnemy(JM_Entity* enemy);

    int getNumberOfEnemies();
    int getActiveEnemies();
    int getInactiveEnemies();

    void reset();
    
    ~JM_EnemyFactory();
};

}

#endif