#include "shield.hpp"

Shield::Shield(SDL_Renderer* renderer) {
    shieldTexture = loadtexture("shield.png", renderer); // Đảm bảo rằng đường dẫn đúng
    if (shieldTexture == nullptr) {
        std::cerr << "Failed to load shield texture: " << SDL_GetError() << std::endl;
    }
    shieldRect = { rand() % (SCREEN_WIDTH - 50), rand() % (SCREEN_HEIGHT - 50), 50, 50 };
    isActive = false;
}

void Shield::render(SDL_Renderer* renderer) {
    if (shieldTexture != nullptr && isActive) {
        SDL_RenderCopy(renderer, shieldTexture, NULL, &shieldRect);
    }
}

bool Shield::checkCollision(SDL_Rect* rect) {
    return SDL_HasIntersection(rect, &shieldRect);
}

void Shield::resetPosition() {
    shieldRect.x = rand() % (SCREEN_WIDTH - shieldRect.w);
    shieldRect.y = rand() % (SCREEN_HEIGHT - shieldRect.h);
}
