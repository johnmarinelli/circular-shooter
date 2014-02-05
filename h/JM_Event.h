/*
* event system to send messages between entities.
*/

#ifndef _JM_EVENT_H
#define _JM_EVENT_H

namespace JM_Library
{
    //forward declaration
    class JM_Entity;

    const int EVENT_TYPES = 4;

    enum JM_EventType
    {
        EVENT_TYPE_NULL,
        EVENT_TYPE_DECREASEHEALTH,
        EVENT_TYPE_INTERACT,
        EVENT_TYPE_SPAWNBULLET,
    };

    struct JM_Event
    {
        JM_Entity* m_addresser;
        JM_EventType m_eventType;

        int toInt()
        {
            return (int)m_eventType;
        };
    };
}

#endif