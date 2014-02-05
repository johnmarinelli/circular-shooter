/*
* special positioncomponent for storage of circular data rather than rectangular
*/

#ifndef _JM_PLAYERPOSITIONCOMPONENT_H
#define _JM_PLAYERPOSITIONCOMPONENT_H

#include "JM_PositionComponent.h"
#include "JM_CollisionCircle.h"
#include "JM_2DVector.h"

namespace JM_Library
{

class JM_PlayerPositionComponent :
    public JM_PositionComponent
{
public:
    JM_CollisionCircle m_collisionCircle;
    JM_2DVector<float> m_origin;
    float m_originRadius;

    float m_angle;
    float m_velocity;

    JM_PlayerPositionComponent();

    void initialize(float originx, float originy, float xPos, float yPos, float radius);

    void update(int dTime);

    void reset();
    JM_CollisionCircle& getCircle();

    ~JM_PlayerPositionComponent();
};

}

#endif

