#include "JM_CollisionSystem.h"
#include "JM_Utilities.h"

namespace JM_Library
{

double distance(const float &x1, const float &y1, const float &x2, const float &y2)
{
	return std::sqrt(std::pow(x2-x1, 2) + std::pow(y2-y1, 2));
}
    
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;

    return true;
}

bool checkCollision(const JM_RectF& a, const JM_RectF& b)
{
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;

    return true;
}

bool checkCollision(const JM_CollisionCircle& a, const JM_RectF& b)
{
    /*closest points*/
	int cX, cY;

    if(a.m_xPosition < b.x) cX = b.x;
    else if(a.m_xPosition > b.x + b.w) cX = b.x + b.w;
    else cX = a.m_xPosition;
    
    if(a.m_yPosition < b.y) cY = b.y;
    else if(a.m_yPosition > b.y + b.h) cY = b.y + b.h;
    else cY = a.m_yPosition;

    if(distance(a.m_xPosition, a.m_yPosition, cX, cY) < a.m_radius) return true;
    else return false;
}

bool checkCollision(const JM_CollisionCircle& a, const JM_CollisionCircle& b)
{
    if(distance(a.m_xPosition, a.m_yPosition, b.m_xPosition, b.m_yPosition) < a.m_radius + b.m_radius) return true;
    else return false;
}

JM_CollisionSystem::JM_CollisionSystem()
    : m_playerPosition(NULL), m_playerHits(0), m_playerHitsDirty(false), m_enemiesEscaped(0)
{
    m_systemType = SYSTEM_TYPE_COLLISION;
    m_screenBox.x = 0;
    m_screenBox.y = 0;
    m_screenBox.w = SCREEN_WIDTH;
    m_screenBox.h = SCREEN_HEIGHT;
}

void JM_CollisionSystem::update(int dTime)
{
    CollisionSystemIterator enemyitr;
    CollisionSystemIterator bulletitr;
    
    for(enemyitr = m_enemyComponents.begin(); enemyitr != m_enemyComponents.end(); ++enemyitr)
    {
        //enemy vs bullets
        for(bulletitr = m_bulletComponents.begin(); bulletitr != m_bulletComponents.end(); )
        {
            if(checkCollision((*enemyitr)->m_collisionBox, (*bulletitr)->m_collisionBox))
            {
                JM_Event decreasehealth;
                decreasehealth.m_addresser = (*bulletitr)->getOwner();
                decreasehealth.m_eventType = EVENT_TYPE_DECREASEHEALTH;
                (*bulletitr)->getOwner()->setTarget((*enemyitr)->getOwner()->m_id);
                (*bulletitr)->getOwner()->sendMessage(decreasehealth);

                (*bulletitr)->getOwner()->m_isActive = false;
                bulletitr = m_bulletComponents.erase(bulletitr);
            }
            
            else
                ++bulletitr;
        }

        //player vs. enemy
        if(checkCollision(m_playerPosition->getCircle(), (*enemyitr)->m_collisionBox)){
            //decrease player health
            JM_Event decreasehealth;
            decreasehealth.m_addresser = (*enemyitr)->getOwner();
            decreasehealth.m_eventType = EVENT_TYPE_DECREASEHEALTH;
            (*enemyitr)->getOwner()->setTarget(m_playerPosition->getOwner()->m_id);
            (*enemyitr)->getOwner()->sendMessage(decreasehealth);
            m_playerHits++;
            m_playerHitsDirty = true;

            //decrease enemy health
            JM_Event dh_enemy;
            dh_enemy.m_addresser = m_playerPosition->getOwner();
            dh_enemy.m_eventType = EVENT_TYPE_DECREASEHEALTH;
            m_playerPosition->getOwner()->setTarget((*enemyitr)->getOwner()->m_id);
            m_playerPosition->getOwner()->sendMessage(dh_enemy);
        }
    }

    //offscreen 
    for(enemyitr = m_enemyComponents.begin(); enemyitr != m_enemyComponents.end(); ){
        SDL_Rect enemybox = (*enemyitr)->m_collisionBox.toRect();

        if(!checkCollision(m_screenBox, enemybox)){
            (*enemyitr)->getOwner()->m_pointsAwarded = 0;
            (*enemyitr)->getOwner()->m_isActive = false;
            enemyitr = m_enemyComponents.erase(enemyitr);

            m_enemiesEscaped++;
            printf("Enemies escaped: %d\n", m_enemiesEscaped);
        }

        else
            ++enemyitr;
    }
    
    for(bulletitr = m_bulletComponents.begin(); bulletitr != m_bulletComponents.end(); ){
        SDL_Rect bulletbox = (*bulletitr)->m_collisionBox.toRect();

        if(!checkCollision(m_screenBox, bulletbox)){
            (*bulletitr)->getOwner()->m_isActive = false;
            bulletitr = m_bulletComponents.erase(bulletitr);
        }
        
        else 
            ++bulletitr;
    }
}

void JM_CollisionSystem::addComponent(JM_BaseComponent* component, JM_OwnerType ownertype)
{
    switch(ownertype){
    case OWNERTYPE_PLAYER: m_playerPosition = static_cast<JM_PlayerPositionComponent*>(component); break;
    case OWNERTYPE_ENEMY: m_enemyComponents.push_back(static_cast<JM_PositionComponent*>(component)); break;
    case OWNERTYPE_BULLET: m_bulletComponents.push_back(static_cast<JM_PositionComponent*>(component)); break;
    default: break;
    }
}

void JM_CollisionSystem::removeComponent(int id)
{
    CollisionSystemIterator itr = m_enemyComponents.begin();

    while(itr != m_enemyComponents.end()){
        if((*itr)->getID() == id){
            itr = m_enemyComponents.erase(itr);
            return;
        }

        else
            ++itr;
    }

    itr = m_bulletComponents.begin();

    while(itr != m_bulletComponents.end()){
        if((*itr)->getID() == id){
            itr = m_bulletComponents.erase(itr);
            return;
        }

        else
            ++itr;
    }
}

void JM_CollisionSystem::clearSystem()
{
    m_playerHits = 0;
    m_enemiesEscaped = 0;
    m_enemyComponents.clear();
    m_bulletComponents.clear();
}

JM_CollisionSystem::~JM_CollisionSystem()
{
}

}