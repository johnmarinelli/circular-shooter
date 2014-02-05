#include "JM_GUI.h"

namespace JM_Library
{
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

JM_GUI::JM_GUI()
    : m_screen(NULL), m_font(TTF_OpenFont("00TT.TTF", 18))
{
    if(m_font == NULL)
        printf("m_font is NULL!  JM_GUI\n");
}

void JM_GUI::setScreen(SDL_Surface* screen)
{
    m_screen = screen;
}

void JM_GUI::addElement(JM_GUIElement* element)
{
    element->setFont(m_font);
    m_elements.push_back(element);
}

JM_GUIElement* JM_GUI::getElement(JM_GUIElementTypes type)
{ 
    GUIElementsIterator itr = m_elements.begin();

    for(; itr != m_elements.end(); ++itr){
        if((*itr)->m_type == type){
            return (*itr);
        }
    }

    //printf("Element not found!! JM_GUI::getElement\n");
    return NULL;
}

JM_GUIElementTypes JM_GUI::handleClick(int x, int y)
{
    GUIElementsIterator itr = m_elements.begin();
    SDL_Rect mouseclick = { x, y, MOUSECLICKBOX_WIDTH, MOUSECLICKBOX_HEIGHT };

    for(; itr != m_elements.end(); ++itr){
        if(checkCollision((*itr)->getBox(), mouseclick)){
            return (*itr)->m_type;
        }
    }

    return ELEMENTTYPE_NULL;
}

void JM_GUI::update(int dTime)
{
}

void JM_GUI::render()
{
    GUIElementsIterator itr = m_elements.begin();

    for(; itr != m_elements.end(); ++itr){
        (*itr)->render(m_screen);
    }
}

JM_GUI::~JM_GUI()
{
    //delete m_elements
}

}
