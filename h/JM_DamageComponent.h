/*
* component to calculate damage inflicted upon collision
*/

#ifndef _JM_DAMAGECOMPONENT_H
#define _JM_DAMAGECOMPONENT_H

#include "JM_BaseComponent.h"

namespace JM_Library
{

class JM_DamageComponent :
    public JM_BaseComponent
{
public:
    int m_damage;

    JM_DamageComponent();

    void reset();

    ~JM_DamageComponent();
};

}

#endif