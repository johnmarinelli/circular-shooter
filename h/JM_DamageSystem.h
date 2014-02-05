/*
* system to work on damage components
*/

#ifndef _JM_DAMAGESYSTEM_H
#define _JM_DAMAGESYSTEM_H

#include "JM_BaseSystem.h"
#include "JM_DamageComponent.h"

namespace JM_Library
{

class JM_DamageSystem :
    public JM_BaseSystem
{
private:
    typedef std::vector<JM_DamageComponent*> DamageComponentVector;
    typedef DamageComponentVector::iterator DamageComponentIterator;

    DamageComponentVector m_components;

    void addComponent(JM_DamageComponent* component);

public:
    JM_DamageSystem();

    void update(int dTime);

    JM_DamageComponent* createComponent(JM_ComponentType type);
    void removeComponent(int id);

    void clearSystem();

    ~JM_DamageSystem();
};

}

#endif