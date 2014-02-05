/*
* component to store state of an entities' health
*/

#ifndef _JM_HEALTHCOMPONENT_H
#define _JM_HEALTHCOMPONENT_H

#include "JM_BaseComponent.h"

namespace JM_Library
{

class JM_HealthComponent :
    public JM_BaseComponent
{
public:
    int m_health;

    JM_HealthComponent();

    void update(int dTime);

    void reset();

    ~JM_HealthComponent();
};

}

#endif
