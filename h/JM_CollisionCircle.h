/*
* collision circle helper class for player entity
*/

#ifndef _JM_COLLISIONCIRCLE_H
#define _JM_COLLISIONCIRCLE_H

namespace JM_Library
{

class JM_CollisionCircle
{
public:
    JM_CollisionCircle();

    float m_xPosition, m_yPosition;
    float m_radius;

    void initialize(float x, float y, float radius);

    void reset();

    ~JM_CollisionCircle();
};

}
#endif