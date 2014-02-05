#include "JM_Game.h"
#include "JM_Timer.h"
#include <time.h>
#include "SDL_ttf.h"

bool running;
const int FPS = 30;

int main(int argc, char* args[])
{ 
    //start sdl & ttf
    SDL_Init(SDL_INIT_EVERYTHING);
    if(TTF_Init() == -1) printf("Problem initializing TTF\n");

    //seed random
    std::srand(time(NULL));

    //make sure you initialize screen before optimized image
    SDL_Surface* screen = SDL_SetVideoMode(JM_Library::SCREEN_WIDTH, JM_Library::SCREEN_HEIGHT, 32, SDL_SWSURFACE);

    running = true;
    int dTime = 0;

    printf("GAMEPLAY:\n");
    printf("Left & Right Arrow Keys: Move\n");
    printf("Spacebar: Shoot\n");
    printf("'p' (lowercase): Pause/Unpause while in game\n");
    printf("\n\n");
    printf("Squares are invading the harmonious land of Circleton through a malicious, \nfinite-sided portal!\nIt's up to you to protect your town's perfect and infinitely symmetrical ways!\n\n");
    printf("RULES: \n");
    printf("Each level with have an amount of enemies equivalent to the level number; eg: Level 11 will have 11 enemies. \n");
    printf("Game is over when you run out of health, or let more than half the total number of enemies escape. \n");
    printf("After each level, you'll have an oppurtunity to buy bullets, health, or an upgrade to make your bullets stronger. \n");
    printf("Yellow Squares have 1 health, Brown Squares have 2 health, and Black Squares have 3 health. \n");

    using namespace JM_Library;
    
    JM_Timer timer;
    JM_Game game(screen);
    timer.start();

    while(running){
        game.handleInput();

        dTime = timer.getTicks();
        game.update(dTime);
        timer.start();

        game.render();
        
        if(dTime <  1000 / FPS) SDL_Delay((1000 / FPS) - dTime);
    }

    SDL_FreeSurface(screen);

    //quit SDL 
	SDL_Quit(); 

	return 0; 
}