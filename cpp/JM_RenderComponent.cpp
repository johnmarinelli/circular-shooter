#include "JM_RenderComponent.h"
#include "JM_PlayerPositionComponent.h"
#include "JM_Utilities.h"

namespace JM_Library{

JM_RenderComponent::JM_RenderComponent()
    : m_GFX(NULL)
{
    m_type = TYPE_RENDER;
}

void JM_RenderComponent::setGFX(std::string path)
{
    m_GFX = loadImage(path);
}

void JM_RenderComponent::update()
{
}

void JM_RenderComponent::render(SDL_Surface* screen)
{
    if(m_owner != NULL){
        JM_PositionComponent* pc = static_cast<JM_PositionComponent*>(m_owner->getComponent(TYPE_POSITION));

        if(pc){
            int xpos = pc->m_collisionBox.x;// - (pc->m_collisionBox.w /2 );
            int ypos = pc->m_collisionBox.y;// - (pc->m_collisionBox.h / 2);
            applySurface(xpos, ypos,m_GFX,screen);
        }

        else
            printf("Position Component is null!! JM_RenderComponent %d\n", m_owner);
    }

    else
        printf("Owner is null!! JM_RenderComponent %d\n", this);
}

void JM_RenderComponent::reset()
{
    m_GFX = NULL;
}

void JM_RenderComponent::initialize()
{
}

JM_RenderComponent::~JM_RenderComponent()
{
}

};