/*
* This is the base class for systems (rendering, AI, movement, etc) to derive from
* every system will have to update something.
*/

#ifndef _JM_BASESYSTEM_H
#define _JM_BASESYSTEM_H

#include <vector>
#include <algorithm>
#include "JM_BaseComponent.h"

namespace JM_Library{

/*functor for deleting object using std::for_each*/
struct JM_DeleteObject
{
    template<class T>
    void operator()(const T* ptr) const
    {
        delete ptr;
        ptr = NULL;
    }
};

enum JM_SystemType
{
    SYSTEM_TYPE_RENDER,
    SYSTEM_TYPE_POSITION,
    SYSTEM_TYPE_INPUT,
    SYSTEM_TYPE_COLLISION,
    SYSTEM_TYPE_HEALTH,
    SYSTEM_TYPE_DAMAGE,
};

class JM_BaseSystem
{
public:
    typedef std::vector<JM_BaseComponent*> SystemComponentVector;
    typedef SystemComponentVector::iterator SystemComponentIterator;
    JM_SystemType m_systemType;

    virtual void update(int dTime) = 0;
    virtual JM_BaseComponent* createComponent(JM_ComponentType type) { return NULL; };
    virtual void addComponent(JM_BaseComponent* component) { } ;
    virtual void removeComponent(int id) = 0;
    virtual void clearSystem() = 0;

    //operator ()() instead of update for std::for_each support

    virtual ~JM_BaseSystem() {};
};

}

#endif