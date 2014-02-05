/*
* Base component class for all components to inherit from.
* Systems work on the components, entities simply have handles 
* to a component but don't actually do any work with the data.
*/

#ifndef _JM_BASECOMPONENT_H
#define _JM_BASECOMPONENT_H

#include "JM_Entity.h"
#include "JM_Event.h"

namespace JM_Library{
    
template<typename T>
void safeDelete(T* t)
{
    delete t;
    t = NULL;
}

class JM_BaseSystem;

enum JM_ComponentType
{
    TYPE_RENDER,
    TYPE_ANIMATION,
    TYPE_POSITION,
    TYPE_INPUT,
    TYPE_HEALTH,
    TYPE_DAMAGE,
};

class JM_BaseComponent
{
protected:
    JM_Entity* m_owner;
    JM_BaseSystem* m_parentSystem;
    int m_id;

public:
    JM_ComponentType m_type;

    JM_BaseComponent();
    JM_BaseComponent(const JM_BaseComponent& c);
    JM_BaseComponent& operator=(const JM_BaseComponent& c);

    virtual void update(int dTime);
    
    void setOwner(JM_Entity* owner);
    void setParentSystem(JM_BaseSystem* system);

    JM_Entity* getOwner();
    JM_BaseSystem* getParentSystem();
    int getID() const;

    virtual void sendMessage();
    virtual void receiveMessage(JM_Event msg);
    //void unregister() will be called in system::removecomponent so that the system
    //will take care of removing the component from itself AND the components owner

    virtual void reset();

    virtual ~JM_BaseComponent();
};

};
#endif