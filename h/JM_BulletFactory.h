/*
* Pool pattern so we don't have to 'new' bullets more than 50x.
* once a bullet is inactive, it gets recycled into the inactive bullets
* and new bullets are spawned from inactive bullets.
*/

#ifndef _JM_BULLETFACTORY_H
#define _JM_BULLETFACTORY_H

#include "JM_Entity.h"
#include "JM_RenderingSystem.h"
#include "JM_PositionSystem.h"
#include "JM_DamageSystem.h"

namespace JM_Library
{

const int MAX_BULLETS_ONSCREEN = 50;
const int BULLET_SIDE = 5;
const int BULLET_VELOCITY = 100;

class JM_BulletFactory
{
private:
    typedef std::vector<JM_Entity*> BulletVector;
    typedef BulletVector::iterator BulletIterator;

    BulletVector m_activeBullets;
    BulletVector m_inactiveBullets;

    int m_playerClipSize;

public:
    JM_BulletFactory();

    void initialize(int clipsize);

    JM_Entity* spawnBullet(float x, float y, JM_RenderingSystem& rendersystem, JM_PositionSystem& positionsystem, JM_DamageSystem& damagesystem);
    void returnBullet(JM_Entity* bullet);

    int getPlayerClipSize();

    ~JM_BulletFactory();
};

}

#endif

