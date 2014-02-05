/*
* basic gui element - used for displaying text on screen.
*/

#ifndef _JM_GUIELEMENT_H
#define _JM_GUIELEMENT_H

#include "JM_SDL.h"
#include "SDL_ttf.h"
#include <string>

namespace JM_Library
{

enum JM_GUIElementTypes
{   
    ELEMENTTYPE_NULL,
    ELEMENTTYPE_START,
    ELEMENTTYPE_BULLET,
    ELEMENTTYPE_LIVES,
    ELEMENTTYPE_POINTS,
    ELEMENTTYPE_LEVEL,
    ELEMENTTYPE_ERROR,
    BUTTONELEMENTTYPE_QUIT,
    BUTTONELEMENTTYPE_BUYBULLETS,
    BUTTONELEMENTTYPE_UPGRADEBULLETS,
    BUTTONELEMENTTYPE_BUYLIFE,
    BUTTONELEMENTTYPE_CONTINUE,
};

class JM_GUIElement
{
private:
    SDL_Surface* m_GFX;
    TTF_Font* m_font;
    SDL_Surface* m_message;

    std::string m_text;

    SDL_Rect m_position;

    void setMessage();

public:
    JM_GUIElementTypes m_type;

    JM_GUIElement();

    void setPosition(int x, int y, int w, int h);
    void setGFX(std::string path);
    void setFont(TTF_Font* font);
    void setText(std::string text);

    TTF_Font* getFont();
    SDL_Surface* getMessage();
    const SDL_Rect& getBox();

    virtual void render(SDL_Surface* screen);

    ~JM_GUIElement();
};

}

#endif