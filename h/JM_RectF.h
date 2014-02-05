/*
* SDL_Rect with floats
*/

#ifndef _JM_RECTF_H
#define _JM_RECTF_H

namespace JM_Library
{
    struct JM_RectF
    {
        float x;
        float y;
        float w;
        float h;

        JM_RectF()
            : x(0.f), y(0.f), w(0.f), h(0.f)
        {
        };

        SDL_Rect toRect()
        {
            SDL_Rect rect = { (int)x, (int)y, (int)w, (int)h };
            return rect;
        };
    };
}

#endif