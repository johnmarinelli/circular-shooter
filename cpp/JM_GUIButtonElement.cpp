#include "JM_GUIButtonElement.h"

namespace JM_Library
{

JM_GUIButtonElement::JM_GUIButtonElement(JM_GUIElementTypes type)
{
    m_type = type;
    setGFX("GFX/defaultbutton.png");
}

JM_GUIButtonElement::~JM_GUIButtonElement()
{
}

}