#ifndef _JM_COMPONENT_H
#define _JM_COMPONENT_H

#include "JM_BaseComponent.h"
#include "JM_PositionComponent.h"
#include "JM_RenderComponent.h"
#include "JM_InputComponent.h"

namespace JM_Library{

/*
**This class is used as an implementation of the ABC BaseComponent, 
**and is used to be changed to & from different kinds of Components
*/
class JM_Component : 
    public JM_BaseComponent
{
public:
    JM_Component();
    JM_Component(const JM_Component& c);
    JM_Component& operator=(const JM_Component& c);

    void initialize();
    void update(int dTime);

    void reset();
    
    ~JM_Component();
};

JM_Component::JM_Component()
{
};

void JM_Component::initialize()
{
    m_owner = NULL;
    m_parentSystem = NULL;
};

void JM_Component::update(int dTime)
{
};

void JM_Component::reset()
{
};

JM_Component::~JM_Component()
{
};

};

#endif