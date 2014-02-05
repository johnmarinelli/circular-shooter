#include "JM_BaseComponent.h"
#include "JM_Entity.h"
#include "JM_BaseSystem.h"

namespace JM_Library{

static int id_counter = 0;

JM_BaseComponent::JM_BaseComponent()
    : m_id(++id_counter), m_owner(NULL), m_parentSystem(NULL)
{
}

JM_BaseComponent::JM_BaseComponent(const JM_BaseComponent &c)
{
    m_id = c.m_id;
    m_owner = NULL;

    ++id_counter;
}

JM_BaseComponent& JM_BaseComponent::operator=(const JM_BaseComponent& c)
{
    m_id = c.m_id;
    m_owner = NULL;
    
    ++id_counter;
    return *this;
}

void JM_BaseComponent::update(int dTime)
{
}

void JM_BaseComponent::setOwner(JM_Entity* owner)
{
    m_owner = owner;
}

void JM_BaseComponent::setParentSystem(JM_BaseSystem* system)
{
    m_parentSystem = system;
}

JM_Entity* JM_BaseComponent::getOwner()
{
    return m_owner;
}

JM_BaseSystem* JM_BaseComponent::getParentSystem()
{
    return m_parentSystem;
}

int JM_BaseComponent::getID() const
{
    return m_id;
}

void JM_BaseComponent::sendMessage()
{
}

void JM_BaseComponent::receiveMessage(JM_Event msg)
{
}

void JM_BaseComponent::reset()
{
    m_owner = NULL;
    m_parentSystem = NULL;
}

JM_BaseComponent::~JM_BaseComponent()
{
    //m_owner = NULL;
    //m_parentSystem = NULL;
}

};