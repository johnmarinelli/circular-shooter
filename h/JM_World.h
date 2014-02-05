/*
* holds data about systems, factories, & entities.
* only one per game instance.  is reset every time a new level is created.
*/

#ifndef _JM_WORLD_H
#define _JM_WORLD_H

#include "JM_Entity.h"
#include "JM_EnemyFactory.h"
#include "JM_BulletFactory.h"
#include "JM_PlayerStats.h"

#include "JM_RenderingSystem.h"
#include "JM_InputSystem.h"
#include "JM_PositionSystem.h"
#include "JM_DamageSystem.h"

#include "JM_TileMap.h"

#include "JM_BaseStateMachine.h"

#include "JM_GameStates.h"
#include "JM_PostOffice.h"

namespace JM_Library
{

class JM_World
{
private:
    JM_World(const JM_World &c);
    JM_World& operator=(const JM_World &c);

    typedef std::vector<JM_Entity*> EntityVector;
    typedef EntityVector::iterator EntityIterator;

    EntityVector m_entities;

    JM_RenderingSystem m_renderSystem;
    JM_InputSystem m_inputSystem;
    JM_PositionSystem m_positionSystem;
    JM_HealthSystem m_healthSystem;
    JM_DamageSystem m_damageSystem;

    JM_EnemyFactory m_enemyFactory;

    JM_BulletFactory m_bulletFactory;

    JM_PostOffice m_postOffice;

    JM_GameStates m_nextState;
    
    JM_PlayerStats& m_playerStats;

    unsigned int& m_level;

    void addEntity(JM_Entity& entity);

public:
    JM_World(SDL_Surface* screen, JM_PlayerStats& stats, unsigned int& m_level);

    void spawnPlayer();

    void spawnEnemy();
    void spawnBullet(float x, float y);

    JM_Entity* createEntity();
    void removeEntity(int entityID);

    void handleInput();
    void update(int dTime);
    void render();

    void checkHealth();
    void checkEnemies();

    void sendMessage(JM_Event msg, int entityID);

    void reset(bool isgameover = false);

    template<typename T>
    T getData(std::string dataType);

    void setNextState(JM_GameStates state);
    JM_GameStates getNextState();

    ~JM_World();
};

//for world->gui communication
template<typename T>
T JM_World::getData(std::string dataType)
{
    if(dataType == "bulletcount") return m_bulletFactory.getPlayerClipSize();
    else if(dataType == "pointscount") return m_playerStats.m_points;
    else if(dataType == "levelcount") return m_level;
    else if(dataType == "healthcount") return m_playerStats.m_health;
    return NULL;
};

}

#endif