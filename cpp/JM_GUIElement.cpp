#include "JM_GUIElement.h"
#include "JM_Utilities.h"

namespace JM_Library
{

JM_GUIElement::JM_GUIElement()
    : m_GFX(NULL), m_message(NULL)
{
    m_position.x = 0;
    m_position.y = 0; 
    m_position.w = 0;
    m_position.h = 0;
} 

void JM_GUIElement::setPosition(int x, int y, int w, int h)
{
    m_position.x = x;
    m_position.y = y;
    m_position.w = w;
    m_position.h = h;
}

void JM_GUIElement::setFont(TTF_Font* font)
{
    m_font = font;
}

void JM_GUIElement::setGFX(std::string path)
{
    m_GFX = loadImage(path);
    if(m_GFX == NULL){
        m_GFX = loadImage("GFX/defaultbutton");
    }
}

void JM_GUIElement::setMessage()
{
    if(m_message) SDL_FreeSurface(m_message);

    SDL_Color textColor = { 0, 0, 0 };
    m_message = TTF_RenderText_Solid(getFont(), m_text.c_str(), textColor);
}

void JM_GUIElement::setText(std::string text)
{
    m_text = text;
    setMessage();
}

TTF_Font* JM_GUIElement::getFont()
{
    return m_font;
}

void JM_GUIElement::render(SDL_Surface* screen)
{
    if(m_GFX) applySurface(m_position.x, m_position.y, m_GFX, screen);
    if(m_message) applySurface(m_position.x, m_position.y, m_message, screen);
}

SDL_Surface* JM_GUIElement::getMessage()
{
    return m_message;
}

const SDL_Rect& JM_GUIElement::getBox()
{
    return m_position;
}

JM_GUIElement::~JM_GUIElement()
{
    SDL_FreeSurface(m_GFX);
    m_GFX = NULL;
    SDL_FreeSurface(m_message);
    m_message = NULL;
}

}