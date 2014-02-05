/*
* constants and widely used functions
*/
#ifndef _JM_UTILITIES_H
#define _JM_UTILITIES_H

#include "JM_SDL.h"
#include <string>

namespace JM_Library
{
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;
const float PLAYER_CIRCLE_RADIUS = 13.5;

//takes in: path to a spritesheet/imagefile, and rgb values that you want transparent
//spits out: a POINTER to an optimized image
SDL_Surface* loadImage(std::string path, Uint8 r = 0xFF, Uint8 g = 0xFF, Uint8 b = 0xFF);

//takes in: x & y coords of where you want the image displayed, the source image, the screen(dest) and a spritesheet clip
void applySurface(int x, int y, SDL_Surface* src, SDL_Surface* dest, SDL_Rect* clip = NULL);

//returns random int between lowerbound and higherbound
template <typename T>
T getRandom(T min, T max)
{
    //return ( rand() % (int)(max + 1 - min) ) + min;
    T randVal = min + static_cast <T>( rand()) /(static_cast <T> (RAND_MAX/(max-min)));

    return randVal;
};

template <typename T>
std::string numberToString (T num)
{
    std::ostringstream ss;
    ss << num;
    return ss.str();
};

int randomWithDistribution(int optsArray[], int freqArray[]);

}

#endif