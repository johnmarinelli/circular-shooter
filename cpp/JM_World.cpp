#include "JM_World.h"
#include "JM_MainMenuState.h"
#include "JM_PlayerPositionComponent.h"
#include "JM_DamageComponent.h"

namespace JM_Library
{

JM_World::JM_World(SDL_Surface* screen, JM_PlayerStats& stats, unsigned int& level)
    : m_playerStats(stats), m_nextState(STATE_NULL), m_level(level)
{
    m_renderSystem.setScreen(screen);
    m_bulletFactory.initialize(stats.m_bullets);
    
    spawnEnemy();
    spawnPlayer();
}

JM_World::JM_World(const JM_World &c)
    : m_playerStats(c.m_playerStats), m_level(c.m_level)
{
    m_entities = c.m_entities;

    m_renderSystem = c.m_renderSystem;
    m_inputSystem = c.m_inputSystem;
    m_positionSystem =  c.m_positionSystem;
    m_healthSystem = c.m_healthSystem;
    m_damageSystem = c.m_damageSystem;
    
    m_enemyFactory = c.m_enemyFactory;
    m_bulletFactory = c.m_bulletFactory;

    m_postOffice = c.m_postOffice;
}

JM_World& JM_World::operator=(const JM_World &c)
{
    m_playerStats = c.m_playerStats;
    
    m_entities = c.m_entities;
    m_level = c.m_level;

    m_renderSystem = c.m_renderSystem;
    m_inputSystem = c.m_inputSystem;
    m_positionSystem =  c.m_positionSystem;
    m_healthSystem = c.m_healthSystem;
    m_damageSystem = c.m_damageSystem;
    
    m_enemyFactory = c.m_enemyFactory;
    m_bulletFactory = c.m_bulletFactory;

    m_postOffice = c.m_postOffice;
    
    return *this;
}

void JM_World::spawnPlayer()
{
    JM_Entity* player = createEntity();

    player->m_type = ENTITYTYPE_PLAYER;

    JM_RenderComponent* rc = m_renderSystem.createComponent(TYPE_RENDER);
    rc->setGFX("GFX/playerdot.png");

    JM_PlayerPositionComponent* pc =  new JM_PlayerPositionComponent; //remember to delete this
    pc->initialize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, PLAYER_CIRCLE_RADIUS);

    m_positionSystem.addComponent(pc, OWNERTYPE_PLAYER);

    JM_InputComponent* ic = m_inputSystem.createComponent(TYPE_INPUT);

    JM_HealthComponent* hc = m_healthSystem.createComponent(TYPE_HEALTH);
    hc->m_health = m_playerStats.m_health;

    JM_DamageComponent* dc = m_damageSystem.createComponent(TYPE_DAMAGE);
    dc->m_damage = m_playerStats.m_damage;

    player->addComponent(rc);
    player->addComponent(pc);
    player->addComponent(ic);
    player->addComponent(hc);
    player->addComponent(dc);
}

void JM_World::addEntity(JM_Entity& entity)
{
    m_entities.push_back(&entity);
}

void JM_World::spawnEnemy()
{
    JM_Entity* entity = m_enemyFactory.spawnEnemy(m_renderSystem, m_positionSystem, m_healthSystem, m_damageSystem, m_level);

    if(entity == NULL)
        return;

    entity->initialize(this);

    this->addEntity(*entity);
    m_postOffice.addRecipient(entity);
}

void JM_World::spawnBullet(float x, float y)
{
    JM_Entity* entity = m_bulletFactory.spawnBullet(x, y, m_renderSystem, m_positionSystem, m_damageSystem);

    if(entity == NULL)
        return;

    entity->initialize(this);

    this->addEntity(*entity);
    m_postOffice.addRecipient(entity);

    m_playerStats.m_bullets--;
}

//called to create player
JM_Entity* JM_World::createEntity()
{
    JM_Entity* entity = new JM_Entity();
    entity->initialize(this);
    m_entities.push_back(entity);

    m_postOffice.addRecipient(entity);

    return entity;
}

void JM_World::removeEntity(int entityID)
{
    m_postOffice.removeRecipient(entityID);
    
    EntityIterator itr = m_entities.begin();
    
    while(itr != m_entities.end())
    {
        if((*itr)->m_id == entityID){
            (*itr)->unregister();
            safeDelete((*itr));
            itr = m_entities.erase(itr);
        }

        else
            ++itr;
    }
}

void JM_World::handleInput()
{
    m_inputSystem.update(0);
}

void JM_World::update(int dTime)
{
    m_positionSystem.update(dTime);
    m_healthSystem.update(dTime);

    checkHealth();
    checkEnemies();
}

void JM_World::render()
{
    m_renderSystem.update(0);
}

void JM_World::checkHealth()
{
    m_playerStats.m_health -= m_positionSystem.getPlayerHits();

    for(EntityIterator itr = m_entities.begin(); itr != m_entities.end(); ){
        if(!(*itr)->m_isActive){
            if((*itr)->m_type == ENTITYTYPE_BULLET){
                m_bulletFactory.returnBullet(*itr);
            }
            else if((*itr)->m_type == ENTITYTYPE_ENEMY){
                m_enemyFactory.returnEnemy(*itr);
                m_playerStats.m_points += (*itr)->m_pointsAwarded;
            }
            else if((*itr)->m_type == ENTITYTYPE_PLAYER){
                if(m_playerStats.m_health < 1){
                    setNextState(STATE_GAMEOVER);
                }
            }

            (*itr)->unregister();
            itr = m_entities.erase(itr);
        }

        else
            ++itr;
    }
}

void JM_World::checkEnemies()
{
    //check if too many enemies have escaped
    if(m_positionSystem.getEnemiesEscaped() >= std::ceil(m_level / 2.f)){
        setNextState(STATE_GAMEOVER);
    }

    //check to see if there are no enemies left, and player isn't dead
    if(m_enemyFactory.getInactiveEnemies() >= m_level && m_nextState != STATE_GAMEOVER){
        setNextState(STATE_STORE);
    }

    //enemy spawning algorithm:
    //if the total number of enemies SPAWNED is less than the current level
    //then spawn an enemy while the number of ACTIVE enemies is less than current level / 3
    if(m_enemyFactory.getNumberOfEnemies() < m_level){
        while(m_enemyFactory.getActiveEnemies() < std::ceil(m_level / 3.f)){
            spawnEnemy();
        }
    }
}

void JM_World::sendMessage(JM_Event msg, int entityID)
{
    if(!m_postOffice.sendMessage(msg, entityID))
        printf("Message sending failed: %d\n", msg.toInt());
}

void JM_World::reset(bool isgameover)
{
    //delete/reset all components allocated in systems
    m_renderSystem.clearSystem();
    m_inputSystem.clearSystem();
    m_positionSystem.clearSystem();
    m_healthSystem.clearSystem();
    m_damageSystem.clearSystem();
    m_postOffice.reset();
    m_enemyFactory.reset();

    EntityIterator itr = m_entities.begin();

    while(itr != m_entities.end()){
        safeDelete((*itr));
        itr = m_entities.erase(itr);
    }

    if(isgameover){
        m_playerStats.reset();
        m_level = 0; 
    }

    m_bulletFactory.initialize(m_playerStats.m_bullets);
    spawnPlayer();

    if(++m_level > 30){
        m_level = 30;
    }
}

void JM_World::setNextState(JM_GameStates state)
{
    m_nextState = state;
}

JM_GameStates JM_World::getNextState()
{
    JM_GameStates state = m_nextState;
    m_nextState = STATE_NULL;
    return state;
}

JM_World::~JM_World()
{
    std::for_each(m_entities.begin(), m_entities.end(), JM_DeleteObject());
}

}