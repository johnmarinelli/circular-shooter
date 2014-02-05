#include "JM_Entity.h"
#include "JM_Component.h"
#include "JM_BaseSystem.h"
#include "JM_World.h"

#include "JM_EventFunctions.h"

namespace JM_Library{

static int entity_id_counter = 1000;

JM_BaseComponent* getComponentFromType(JM_ComponentType type)
{
    switch(type)
    {
    case TYPE_RENDER: return new JM_RenderComponent();
    case TYPE_POSITION: return new JM_PositionComponent();
    case TYPE_INPUT: return new JM_InputComponent();
    default: return NULL;
    }
}

JM_Entity::JM_Entity()
    : m_world(NULL), m_id(entity_id_counter++), m_isActive(true), m_type(ENTITYTYPE_NULL), m_targetEntityID(0), m_pointsAwarded(1)
{
}

JM_Entity::JM_Entity(const JM_Entity& c)
{
    //make a temporary m, copy const elements of c into that m, and create new vector based on the elements of temp m
    ComponentMap clist = c.m_components;

    //clear our componentmap
    clearComponents();

    for(ComponentIterator itr = clist.begin(); itr != clist.end(); ++itr)
    {
        //retrieve component
        JM_BaseComponent* component;

        //FIX THIS SO IT GETS A COMPONENT FROM WORLD!!
        component = getComponentFromType((*itr).second->m_type);

        //register component with system & set its owner 
        (*itr).second->getParentSystem()->addComponent(component);
        component->setOwner(this);

        this->m_components.insert(ComponentPair(component->m_type, component));
    }

    m_id = entity_id_counter++;
    m_type = c.m_type;
    initialize(c.m_world);
}

JM_Entity& JM_Entity::operator=(const JM_Entity& c) 
{
    //make a temporary m, copy const elements of c into that m, and create new vector based on the elements of temp m
    ComponentMap clist = c.m_components;

    //clear our componentmap
    clearComponents();

    for(ComponentIterator itr = clist.begin(); itr != clist.end(); ++itr)
    {
        //retrieve component
        JM_BaseComponent* component;

        //FIX THIS SO IT GETS A COMPONENT FROM WORLD!!
        component = getComponentFromType((*itr).second->m_type);

        //register component with system & set its owner 
        (*itr).second->getParentSystem()->addComponent(component);
        component->setOwner(this);

        this->m_components.insert(ComponentPair(component->m_type, component));
    }

    m_id = entity_id_counter++;
    m_type = c.m_type;
    initialize(c.m_world);

    return *this;
}

void JM_Entity::initialize(JM_World* world)
{
    m_isActive = true;
    m_world = world;
    m_pointsAwarded = 1;
}

JM_World& JM_Entity::getWorld()
{
    return *m_world;
}

void JM_Entity::addComponent(JM_BaseComponent* component)
{
    if(!hasComponent(component->m_type)){
        component->setOwner(this);
        m_components.insert(ComponentPair(component->m_type, component));
    }
}

bool JM_Entity::hasComponent(JM_ComponentType type)
{
    return (m_components.find(type) == m_components.end()) ? false : true;
}

JM_BaseComponent* JM_Entity::getComponent(JM_ComponentType type)
{
    for(ComponentIterator itr = m_components.begin(); itr != m_components.end(); ++itr){
        if(itr->second->m_type == type){
            return itr->second;
        }
    }

    return NULL;
}

void JM_Entity::removeComponent(JM_ComponentType type)
{
    ComponentIterator itr = m_components.find(type);

    //delete actual memory in the system & remove it from systems' list
    //remove component from the entities' list
    if(itr != m_components.end()){
        itr->second->getParentSystem()->removeComponent(itr->second->getID());
        m_components.erase(itr);
    }
}

void JM_Entity::setTarget(int entityID)
{
    m_targetEntityID = entityID;
}

void JM_Entity::sendMessage(JM_Event msg)
{
    m_world->sendMessage(msg, m_targetEntityID);
}

void JM_Entity::receiveMessage(JM_Event msg)
{
    (*functorArray[msg.toInt()])((*msg.m_addresser), *this);
}

void JM_Entity::clearComponents()
{
    ComponentIterator itr = m_components.begin();

    //SLAP ON THE WRIST FOR TWO LEVELS OF INDIRECTION
    while(itr != m_components.end()){
        (*itr).second->getParentSystem()->removeComponent((*itr).second->getID());

        m_components.erase(itr++);
    }

    m_components.clear();
}

void JM_Entity::unregister()
{
    if(!m_isActive){
        clearComponents();
        m_world = NULL;
    }
}

JM_Entity::~JM_Entity()
{
    m_components.clear();
}

};