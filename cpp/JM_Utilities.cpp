#include "JM_Utilities.h"
#include <random>

namespace JM_Library
{

//takes in: path to a spritesheet/imagefile, and rgb values that you want transparent
//spits out: a POINTER to an optimized image
SDL_Surface* loadImage(std::string path, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    //load image
    loadedImage = IMG_Load(path.c_str());

    if(loadedImage != NULL)
    {
        //create optimized surface
        optimizedImage = SDL_DisplayFormat(loadedImage);
        //free old surface
        SDL_FreeSurface(loadedImage);

        if(optimizedImage != NULL)
        {
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b));
        }

        else
            printf("Optimized image is null\n");
    }

    return optimizedImage;
}

//takes in: x & y coords of where you want the image displayed, the source image, the screen(dest) and a spritesheet clip
void applySurface(int x, int y, SDL_Surface* src, SDL_Surface* dest, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(src, clip, dest, &offset);
}

int getCeiling(int nArray[], int random, int start, int end)
{
	int mid;

	while (start < end){
		mid = (start + end) / 2;

        //if the random number is more than the auxillary arrays' mid number, push the start # forward
		if (random > nArray[mid]){
			start = mid + 1;
		}

        //otherwise, the random number is less than the mid number and end index is pushed backward
		else
			end = mid;
	}

	return (nArray[start] >= random ? start : -1);
}

//generate random number given a distribution
//for enemyfactory to determing which level the enemy will be
int randomWithDistribution(int nArray[], int freqArray[])
{
    const int size = 3;
	int auxArray[size];
	auxArray[0] = freqArray[0];

	for (int i = 1; i < size; ++i){
		auxArray[i] = auxArray[i-1] + freqArray[i];
	}

	//last number of auxArray holds total # of frequencies, the +1 is there for inclusion
	int random = rand() % auxArray[size - 1] + 1;

	int ceiling = getCeiling(auxArray, random, 0, size - 1);
	return nArray[ceiling];
}

}
