/*
* entity.  there are three kinds of entity, and all the entity is aware of is
* its components and its world.
*/

#ifndef _JM_ENTITY_H
#define _JM_ENTITY_H

#include <map>
#include <vector>
#include "JM_Event.h"

namespace JM_Library
{

enum JM_EntityTypes
{
    ENTITYTYPE_NULL,
    ENTITYTYPE_PLAYER,
    ENTITYTYPE_BULLET,
    ENTITYTYPE_ENEMY,
};
    
//forward declaration so we don't have 2 .h files #including each other
class JM_BaseComponent;
class JM_World;

enum JM_ComponentType;

JM_BaseComponent* getComponentFromType(JM_ComponentType);

class JM_Entity
{
private:
    typedef std::map<JM_ComponentType, JM_BaseComponent*> ComponentMap;
    typedef std::pair<JM_ComponentType, JM_BaseComponent*> ComponentPair;
    typedef ComponentMap::iterator ComponentIterator;

    ComponentMap m_components;
    JM_World* m_world;

public:
    JM_EntityTypes m_type;
    bool m_isActive;
    
    int m_id;
    int m_targetEntityID;
    int m_pointsAwarded;

    //copy ctors: return a new entity with new components that are the same type as input components
    JM_Entity();
    JM_Entity(const JM_Entity& c);
    JM_Entity& operator=(const JM_Entity& c);

    void initialize(JM_World* world);
    JM_World& getWorld();

    void addComponent(JM_BaseComponent* component);
    void removeComponent(JM_ComponentType type);

    JM_BaseComponent* getComponent(JM_ComponentType type);
    bool hasComponent(JM_ComponentType type);

    void setTarget(int entityID);
    void sendMessage(JM_Event msg);
    void receiveMessage(JM_Event msg);

    void unregister();

    void clearComponents();

    ~JM_Entity();
};

};

#endif