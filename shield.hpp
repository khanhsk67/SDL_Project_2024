#ifndef SHIELD_HPP
#define SHIELD_HPP

#include <SDL.h>
#include "SDL_func.hpp"

class Shield {
public:
    Shield(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    bool checkCollision(SDL_Rect* rect);
    void resetPosition();

    bool isActive;
    SDL_Rect shieldRect;

private:
    SDL_Texture* shieldTexture;
};

#endif // SHIELD_HPP
