/*
* gui class that handles adding and managing gui elements.
*/

#ifndef _JM_GUI_H
#define _JM_GUI_H

#include "JM_GUIButtonElement.h"
#include "SDL_ttf.h"
#include <vector>

namespace JM_Library
{

const int MOUSECLICKBOX_WIDTH = 5;
const int MOUSECLICKBOX_HEIGHT = 5;

class JM_GUI
{
private:
    typedef std::vector<JM_GUIElement*> GUIElements;
    typedef GUIElements::iterator GUIElementsIterator;

    GUIElements m_elements;

    SDL_Surface* m_screen;
    TTF_Font* m_font;

public:
    JM_GUI();

    void setScreen(SDL_Surface* screen);

    void addElement(JM_GUIElement* element);
    JM_GUIElement* getElement(JM_GUIElementTypes type);

    JM_GUIElementTypes handleClick(int x, int y);

    void update(int dTime);
    void render();

    ~JM_GUI();
};

}
#endif