/*
* gui element that has an on-click capability
*/

#ifndef _JM_GUIBUTTONELEMENT_H
#define _JM_GUIBUTTONELEMENT_H

#include "JM_GUIElement.h"

namespace JM_Library
{

class JM_GUIButtonElement :
    public JM_GUIElement
{
public:
    JM_GUIButtonElement(JM_GUIElementTypes type);
    ~JM_GUIButtonElement();
};

}

#endif