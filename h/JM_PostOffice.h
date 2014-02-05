/*
* class to manage messages being sent and received by entities.
*/

#ifndef _JM_POSTOFFICE_H
#define _JM_POSTOFFICE_H

#include "JM_Entity.h"

namespace JM_Library
{
void initFunctorArray(); //forward declaration from JM_EventFunctions

class JM_PostOffice
{
private:
    typedef std::map<int, JM_Entity*> EntityMap;
    typedef std::pair<int, JM_Entity*> EntityMapPair;
    typedef EntityMap::iterator EntityIterator;

    EntityMap m_recipients;

public:
    JM_PostOffice()
    {
        initFunctorArray(); //initializes the functor array used by messaging systems
    };

    void addRecipient(JM_Entity* recipient)
    {
        m_recipients.insert(EntityMapPair(recipient->m_id, recipient));
    };

    void removeRecipient(int entityID)
    {
        EntityIterator itr = m_recipients.find(entityID);

        if(itr != m_recipients.end()){
            m_recipients.erase(entityID);
        }
    };

    bool sendMessage(JM_Event msg, int entityID)
    {
        EntityIterator itr = m_recipients.find(entityID);

        if(itr != m_recipients.end()){
            itr->second->receiveMessage(msg);
            return true;
        }

        return false;
    };

    void reset()
    {
        m_recipients.clear();
    }
};

}

#endif
