#include "JM_InputComponent.h"
#include "JM_PlayerPositionComponent.h"
#include "JM_Event.h"
#include "JM_World.h"

namespace JM_Library
{

JM_InputComponent::JM_InputComponent()
{
    m_type = TYPE_INPUT;
}

void JM_InputComponent::update()
{
}

void JM_InputComponent::update(SDL_Event& e)
{
    if(m_owner != NULL)
    {
        JM_PlayerPositionComponent* pc = static_cast<JM_PlayerPositionComponent*>(m_owner->getComponent(TYPE_POSITION));

        if(!pc){
            printf("Player Position Component nul!! JM_InputComponent:: m_owner: %d\n", m_owner);
            return;
        }

        if(e.type == SDL_KEYDOWN){

            switch(e.key.keysym.sym)
            {
            case SDLK_LEFT: pc->m_velocity = PLAYER_VELOCITY; break;
            case SDLK_RIGHT: pc->m_velocity = -PLAYER_VELOCITY; break;

            case SDLK_SPACE: 
                JM_Event bulletmsg;
                bulletmsg.m_eventType = EVENT_TYPE_SPAWNBULLET;
                bulletmsg.m_addresser = m_owner;
                m_owner->receiveMessage(bulletmsg); break;

            case SDLK_p: 
                m_owner->getWorld().setNextState(STATE_PAUSE); break;

            default: break;
            }
        }

        else if(e.type == SDL_KEYUP){
            switch(e.key.keysym.sym)
            {
            case SDLK_LEFT: if(pc->m_velocity != 0) pc->m_velocity = 0; break;
            case SDLK_RIGHT: if(pc->m_velocity != 0) pc->m_velocity = 0;  break;
            default: break;
            }
        }

        else if(e.type == SDL_QUIT){
            running = false;
        }
    }
}

void JM_InputComponent::initialize()
{
}

JM_InputComponent::~JM_InputComponent()
{
}

}