/*
* component to handle the input for the game.
*/

#ifndef _JM_INPUTCOMPONENT_H
#define _JM_INPUTCOMPONENT_H

#include "JM_BaseComponent.h"
#include "JM_SDL.h"

namespace JM_Library
{

const float PLAYER_VELOCITY = .05f;

class JM_InputComponent :
    public JM_BaseComponent
{
public:
    JM_InputComponent();

    void initialize();

    void update();
    void update(SDL_Event& e);

    ~JM_InputComponent();
};

}
#endif

