/*
* 2D vector helper class
*/

#ifndef _JM_2DVECTOR_H
#define _JM_2DVECTOR_H

namespace JM_Library
{
    template<class T>
    struct JM_2DVector
    {
        T x, y;

        JM_2DVector()
            : x(0), y(0)
        {
        }

        JM_2DVector(T in_X, T in_Y)
            : x(in_X), y(in_Y)
        {
        }
    };
};

#endif