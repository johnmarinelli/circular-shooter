/*
* system to manage position components.  coupled with a collision system member variable
*/
#ifndef _JM_POSITIONSYSTEM_H
#define _JM_POSITIONSYSTEM_H

#include "JM_BaseSystem.h"
#include "JM_CollisionSystem.h"

namespace JM_Library
{

class JM_PositionSystem :
    public JM_BaseSystem
{
private:
    SystemComponentVector m_components;
    JM_CollisionSystem m_collisionSystem;

public:
    JM_PositionSystem();

    void update(int dTime);
    JM_PositionComponent* createComponent(JM_ComponentType type, JM_OwnerType ownertype);
    void addComponent(JM_BaseComponent* component, JM_OwnerType ownertype);
    void removeComponent(int id);

    const int getPlayerHits();
    const int getEnemiesEscaped();

    void clearSystem();

    ~JM_PositionSystem();
};

}

#endif