/*
* Rendering component: has an SDL_Surface* and renders it
*/

#ifndef _JM_RENDERCOMPONENT_H
#define _JM_RENDERCOMPONENT_H

#include "JM_SDL.h"
#include "JM_BaseComponent.h"

namespace JM_Library
{

class JM_RenderComponent :
    public JM_BaseComponent
{
private:
    SDL_Surface* m_GFX;

public:
    JM_RenderComponent();

    void initialize();

    void setGFX(std::string path);
    void update();

    void render(SDL_Surface* screen);
    
    void reset();

    ~JM_RenderComponent();
};

}
#endif