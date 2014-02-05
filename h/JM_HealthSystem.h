/*
* system to manage health components.
*/

#ifndef _JM_HEALTHSYSTEM_H
#define _JM_HEALTHSYSTEM_h

#include "JM_BaseSystem.h"
#include "JM_HealthComponent.h"

namespace JM_Library
{

class JM_HealthSystem :
    public JM_BaseSystem
{
private:
    typedef std::vector<JM_HealthComponent*> HealthComponentVector;
    typedef HealthComponentVector::iterator HealthComponentIterator;

    HealthComponentVector m_components;
    void addComponent(JM_HealthComponent* component);

public:
    JM_HealthSystem();

    void update(int dTime);

    JM_HealthComponent* createComponent(JM_ComponentType type);
    void removeComponent(int id);
    
    void clearSystem();

    ~JM_HealthSystem();
};

}

#endif