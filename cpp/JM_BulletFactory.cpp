#include "JM_BulletFactory.h"
#include "JM_Utilities.h"

namespace JM_Library
{

JM_BulletFactory::JM_BulletFactory()
    : m_playerClipSize(0)
{
}

void JM_BulletFactory::initialize(int clipsize)
{
    m_playerClipSize = clipsize;

    m_activeBullets.reserve(MAX_BULLETS_ONSCREEN);
    m_inactiveBullets.reserve(MAX_BULLETS_ONSCREEN);

    for(int i = 0; i < clipsize; ++i){
        m_inactiveBullets.push_back(new JM_Entity());
    }
}

JM_Entity* JM_BulletFactory::spawnBullet(float x, float y, JM_RenderingSystem& rendersystem, JM_PositionSystem& positionsystem, JM_DamageSystem& damagesystem)
{
    if(m_playerClipSize > 0){
        BulletIterator itr = m_inactiveBullets.begin();

        JM_Entity* entity = (*itr);

        entity->m_type = ENTITYTYPE_BULLET;

        JM_DamageComponent* dc = damagesystem.createComponent(TYPE_DAMAGE);
        dc->m_damage = 1;
        entity->addComponent(dc);

        JM_PositionComponent* pc = positionsystem.createComponent(TYPE_POSITION, OWNERTYPE_BULLET);
        pc->m_collisionBox.x = x + PLAYER_CIRCLE_RADIUS;
        pc->m_collisionBox.y = y + PLAYER_CIRCLE_RADIUS;
        pc->m_collisionBox.w = BULLET_SIDE;
        pc->m_collisionBox.h = BULLET_SIDE;

        float xdir = (SCREEN_WIDTH / 2.f) - (x + PLAYER_CIRCLE_RADIUS);
        float ydir = (SCREEN_HEIGHT / 2.f) - (y + PLAYER_CIRCLE_RADIUS);

        int magnitude = (int)( std::sqrt(std::pow(xdir, 2.f) + std::pow(ydir, 2.f)) );

        float xvel = (xdir / magnitude) * BULLET_VELOCITY;
        float yvel = (ydir / magnitude) * BULLET_VELOCITY;

        pc->m_xVelocity = xvel;
        pc->m_yVelocity = yvel;

        entity->addComponent(pc);

        JM_RenderComponent* rc = rendersystem.createComponent(TYPE_RENDER);
        rc->setGFX("GFX/bullet.png");
        entity->addComponent(rc);

        //make a transfer from m_activebullets to m_inactivebullets
        m_activeBullets.push_back(entity);
        m_inactiveBullets.erase(itr++);

        m_playerClipSize--;
        return entity;
    }

    else
        return NULL;
}

void JM_BulletFactory::returnBullet(JM_Entity* bullet)
{
    //find bullet location
    BulletIterator itr = m_activeBullets.begin();

    for(; itr != m_activeBullets.end(); )
    {
        if((*itr)->m_id == bullet->m_id){
            m_inactiveBullets.push_back(bullet);
            itr = m_activeBullets.erase(itr);

            return;
        }

        else
            ++itr;
    }
}

int JM_BulletFactory::getPlayerClipSize()
{
    return m_playerClipSize;
}

JM_BulletFactory::~JM_BulletFactory()
{
}

}