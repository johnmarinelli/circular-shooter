#include "JM_EnemyFactory.h"
#include <algorithm>
#include "JM_Utilities.h"
#include <math.h>

#define PI 3.14159265358979323846

namespace JM_Library
{

float degreesToRadians(int degrees)
{
    return degrees * (PI / 180.f);
}

JM_EnemyFactory::JM_EnemyFactory()
    : m_numberOfEnemies(0), m_activeEnemies(0), m_inactiveEnemies(0)
{
    for(int i = 0; i < MAX_ENEMIES; ++i){
        JM_Entity* entity = new JM_Entity();
        m_entityPool.push(entity);
    }
}

JM_Entity* JM_EnemyFactory::spawnEnemy(JM_RenderingSystem& rendersystem, JM_PositionSystem& positionsystem, JM_HealthSystem& healthsystem, JM_DamageSystem& damagesystem, int level)
{
    if(!m_entityPool.empty()){
        JM_Entity* entity = m_entityPool.top();
        m_entityPool.pop();

        int optsarray[3];
        if(std::ceil(level / 10.f) == 1) { optsarray[0] = 1; optsarray[1] = 1; optsarray[2] = 1; }
        else if(std::ceil(level / 10.f) == 2) { optsarray[0] = 1; optsarray[1] = 2; optsarray[2] = 1; }
        else if(std::ceil(level / 10.f) == 3) { optsarray[0] = 1; optsarray[1] = 2; optsarray[2] = 3; }

        int freqarray[] = { 60, 30, 10 } ;
        int enemylevel = randomWithDistribution(optsarray, freqarray);

        entity->m_type = ENTITYTYPE_ENEMY;
        JM_PositionComponent* pc = positionsystem.createComponent(TYPE_POSITION, OWNERTYPE_ENEMY);
        pc->m_collisionBox.x = getRandom((SCREEN_WIDTH / 2.f) - SPAWN_AREA_SIDE, (SCREEN_WIDTH / 2.f) + SPAWN_AREA_SIDE);
        pc->m_collisionBox.y = getRandom((SCREEN_HEIGHT / 2.f) - SPAWN_AREA_SIDE, (SCREEN_HEIGHT / 2.f) + SPAWN_AREA_SIDE);
        pc->m_collisionBox.w = ENEMY_SIDE;
        pc->m_collisionBox.h = ENEMY_SIDE;

        int randomangle = std::rand() % 360;
        pc->m_xVelocity = (ENEMY_VELOCITY_FLOOR + level * ENEMY_VELOCITY_INC) * std::cos(degreesToRadians(randomangle));
        pc->m_yVelocity = (ENEMY_VELOCITY_FLOOR + level * ENEMY_VELOCITY_INC) * std::sin(degreesToRadians(randomangle));

        entity->addComponent(pc);

        JM_RenderComponent* rc = rendersystem.createComponent(TYPE_RENDER);
        if(enemylevel == 1) rc->setGFX("GFX/yellowenemy.png");
        else if(enemylevel == 2) rc->setGFX("GFX/brownenemy.png");
        else if(enemylevel == 3) rc->setGFX("GFX/blackenemy.png");

        entity->addComponent(rc);

        JM_HealthComponent* hc = healthsystem.createComponent(TYPE_HEALTH);
        hc->m_health = enemylevel;
        entity->addComponent(hc);

        JM_DamageComponent* dc = damagesystem.createComponent(TYPE_DAMAGE);
        dc->m_damage = enemylevel;
        entity->addComponent(dc);

        m_numberOfEnemies++;
        m_activeEnemies++;

        return entity;
    }

    else{
        return NULL;
    }
}

void JM_EnemyFactory::returnEnemy(JM_Entity* enemy)
{
    m_entityPool.push(enemy);
    m_activeEnemies--;
    m_inactiveEnemies++;
}

int JM_EnemyFactory::getNumberOfEnemies()
{
    return m_numberOfEnemies;
}

int JM_EnemyFactory::getActiveEnemies()
{
    return m_activeEnemies;
}

int JM_EnemyFactory::getInactiveEnemies()
{
    return m_inactiveEnemies;
}

void JM_EnemyFactory::reset()
{
    m_activeEnemies = 0;
    m_inactiveEnemies = 0;
    m_numberOfEnemies = 0;
    
    for(int i = 0; i < MAX_ENEMIES; ++i){
        JM_Entity* entity = new JM_Entity();
        m_entityPool.push(entity);
    }
}

JM_EnemyFactory::~JM_EnemyFactory()
{
}

}