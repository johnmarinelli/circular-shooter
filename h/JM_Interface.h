/*
* This class acts as a base class for GUI-world interaction
*/

#ifndef _JM_INTERFACE_H
#define _JM_INTERFACE_H

namespace JM_Library
{

class JM_Interface
{
public:
    virtual void update(int dTime) = 0;
    virtual ~JM_Interface();
};

}

#endif
