/*
* this class creates a functor array that's aligned with event types, and 
* returns the appropriate functor according to the type of event.
*/

#ifndef _JM_EVENTFUNCTIONS_H
#define _JM_EVENTFUNCTIONS_H

#include <functional>
#include "JM_Entity.h"
#include "JM_PositionComponent.h"
#include "JM_HealthComponent.h"
#include "JM_DamageComponent.h"

namespace JM_Library
{
    void initFunctorArray();
    
    struct JM_Functor : public std::binary_function<JM_Entity&, JM_Entity&, void>
    {
        virtual void operator()(JM_Entity& sender, JM_Entity& receiver)
        {
        };
    };

    static JM_Functor* functorArray[EVENT_TYPES];
    JM_Functor* createFunctor(int eventtype);

    void initFunctorArray()
    {
        for(int i = EVENT_TYPE_NULL; i < EVENT_TYPES; ++i){
            functorArray[i] = createFunctor(i);
        }
    };

    struct JM_ShootBulletFunctor : public JM_Functor
    {
        void operator()(JM_Entity& sender, JM_Entity& receiver)
        {
            JM_PositionComponent* pc = static_cast<JM_PositionComponent*>(sender.getComponent(TYPE_POSITION));
            
            if(pc){
                sender.getWorld().spawnBullet(pc->m_collisionBox.x, pc->m_collisionBox.y);
            }

            else
                printf("Position Component is null!!  JM_ShootBulletFunctor sender %d\n", sender);
        };
    };
    
    struct JM_InteractFunctor : public JM_Functor
    {
        void operator()(JM_Entity& sender, JM_Entity& receiver)
        {
            printf("Interact: %d sender, %d receiver\n", &sender, &receiver);
        };
    };
    
    struct JM_DecreaseHealthFunctor : public JM_Functor
    {
        void operator()(JM_Entity& sender, JM_Entity& receiver)
        {
            JM_DamageComponent* dc = static_cast<JM_DamageComponent*>(sender.getComponent(TYPE_DAMAGE));
            JM_HealthComponent* hc = static_cast<JM_HealthComponent*>(receiver.getComponent(TYPE_HEALTH));
            
            if(dc && hc){
                hc->m_health -= dc->m_damage;
                //printf("sender hits for %d, receiver health is %d\n", dc->m_damage, hc->m_health);
            }

            else
                printf("damage or health components are null!! sender: %d      receiver %d\n", sender, receiver);
        };
    };


    JM_Functor* createFunctor(int eventtype)
    {
        switch(eventtype)
        {
        case 0: return new JM_Functor; break;
        case 1: return new JM_DecreaseHealthFunctor; break;
        case 2: return new JM_InteractFunctor; break;
        case 3: return new JM_ShootBulletFunctor; break;
        default: return new JM_Functor; break;
        }
    };
}

#endif