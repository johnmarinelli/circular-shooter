/*
* component to manage position and movement of an entity
*/

#ifndef _JM_POSITIONCOMPONENT_H
#define _JM_POSITIONCOMPONENT_H

#include "JM_BaseComponent.h"
#include "JM_SDL.h"
#include "JM_2DVector.h"
#include "JM_RectF.h"

namespace JM_Library
{
    enum JM_OwnerType
    {
        OWNERTYPE_NULL,
        OWNERTYPE_PLAYER,
        OWNERTYPE_ENEMY,
        OWNERTYPE_BULLET,
    };

class JM_PositionComponent :
    public JM_BaseComponent
{
public:
    JM_OwnerType m_ownerType;
    float m_xVelocity, m_yVelocity;
    JM_RectF m_collisionBox;

    JM_PositionComponent();

    void setCollisionBox(const SDL_Rect& box);
    void update(int dTime);

    void reset();

    ~JM_PositionComponent();
};

};

#endif