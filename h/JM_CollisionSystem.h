/*
* collision system.  handles bullet-enemy collision, enemy-player collision,
* and sending messages between entities letting them know who hit who
*/

#ifndef _JM_COLLISIONSYSTEM_H
#define _JM_COLLISIONSYSTEM_H

#include "JM_SDL.h"
#include "JM_CollisionCircle.h"
#include "JM_BaseSystem.h"
#include "JM_PlayerPositionComponent.h"

namespace JM_Library
{
double distance(const float &x1, const float &y1, const float &x2, const float &y2);

class JM_CollisionSystem :
    public JM_BaseSystem
{
private:
    typedef std::vector<JM_PositionComponent*> CollisionSystemComponentVector;
    typedef CollisionSystemComponentVector::iterator CollisionSystemIterator;

    CollisionSystemComponentVector m_enemyComponents;
    CollisionSystemComponentVector m_bulletComponents;
    JM_PlayerPositionComponent* m_playerPosition;

    SDL_Rect m_screenBox;

public:
    //ugly hack :(
    int m_playerHits;
    bool m_playerHitsDirty;

    int m_enemiesEscaped;

    JM_CollisionSystem();

    void update(int dTime);
    void addComponent(JM_BaseComponent* component, JM_OwnerType ownertype = OWNERTYPE_NULL);
    void removeComponent(int ID);

    void clearSystem();

    ~JM_CollisionSystem();
};

}

#endif