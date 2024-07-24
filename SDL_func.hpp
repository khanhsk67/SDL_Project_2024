#ifndef SDl_func

#define SDL_func

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 650;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);



#endif // SDl_func
