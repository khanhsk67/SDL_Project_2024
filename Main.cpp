#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "SDL_func.hpp"
#include "shield.hpp" 

using namespace std;

SDL_Renderer* renderer;
SDL_Window* window;

int movex, movey = 0;

int main(int argc, char* argv[]) {
    srand(time(0));
    initSDL(window, renderer);



    SDL_Texture* background = loadtexture("background.png", renderer);
    SDL_Texture* m9right = loadtexture("m9.png", renderer);
    SDL_Texture* m9left = loadtexture("m9left.png", renderer);
    SDL_Texture* ex = loadtexture("Excalibur.png", renderer);
    SDL_Texture* laser = loadtexture("laser.png", renderer);
    SDL_Texture* ball1 = loadtexture("ball1.png", renderer);
    SDL_Texture* ball2 = loadtexture("ball2.png", renderer);
    SDL_Texture* ball3 = loadtexture("ball3.png", renderer);
    SDL_Texture* ball4 = loadtexture("ball4.png", renderer);
    SDL_Texture* ghost = loadtexture("ghost.png", renderer);
   

    SDL_Rect m9_rect;
    SDL_Rect ex_rect;
    SDL_Rect laser_rect;
    SDL_Rect ball_rect;
    SDL_Rect ghost_rect;

    
    Shield shield(renderer);
    Uint32 shieldStartTime = 3000; 
    Uint32 shieldDuration = 5000; 
    bool isImmortal = false;

    bool cont = true;

    while (cont) {
        bool direct = 1;
        float i = 0.5;
        int li = 4;
        int bi = 1;
        bool x = 1;
        bool m = 1;
        movex = 0;
        movey = 0;

        m9_rect.x = SCREEN_WIDTH / 2 - 70;
        m9_rect.y = SCREEN_HEIGHT / 2 - 50;
        m9_rect.h = 70;
        m9_rect.w = 50;

        ex_rect.x = 0;
        ex_rect.y = rand() % (SCREEN_HEIGHT - 100) + 10;
        ex_rect.h = 60;
        ex_rect.w = 60;
        int cex = 0;

        laser_rect.x = SCREEN_WIDTH - 50;
        laser_rect.y = rand() % (SCREEN_HEIGHT - 20);
        laser_rect.h = 20;
        laser_rect.w = 50;
        int claser = 0;

        ball_rect.x = SCREEN_WIDTH;
        ball_rect.y = SCREEN_HEIGHT;
        ball_rect.h = 50;
        ball_rect.w = 50;
        int cball = 0;
        float aball = 0.1;
        int bball = 0;

        ghost_rect.x = SCREEN_WIDTH;
        ghost_rect.y = 0;
        ghost_rect.h = 45;
        ghost_rect.w = 45;
        float aghost = 1;
        int bghost = 0;
        int cghost = 0;

        while (x) {
            SDL_RenderCopy(renderer, background, NULL, NULL);


            
            if (!shield.isActive && (rand() % 1000) < 5) {
                shield.isActive = true;
                shield.resetPosition();
            }

           
            shield.render(renderer);

            if (shield.checkCollision(&m9_rect)) {
                isImmortal = true;
                shieldStartTime = SDL_GetTicks();
            }

            if (isImmortal && SDL_GetTicks() - shieldStartTime > shieldDuration) {
                isImmortal = false;
            }

            if (!isImmortal) {
                if (m9_rect.x + m9_rect.w >= ex_rect.x &&
                    ex_rect.x + ex_rect.w >= m9_rect.x &&
                    m9_rect.y + m9_rect.h >= ex_rect.y &&
                    ex_rect.y + ex_rect.h >= m9_rect.y) {
                    x = false;
                }

                if (m9_rect.x + m9_rect.w >= laser_rect.x &&
                    laser_rect.x + laser_rect.w >= m9_rect.x &&
                    m9_rect.y + m9_rect.h >= laser_rect.y &&
                    laser_rect.y + laser_rect.h >= m9_rect.y) {
                    x = false;
                }

                if (m9_rect.x + m9_rect.w >= ball_rect.x &&
                    ball_rect.x + ball_rect.w >= m9_rect.x &&
                    m9_rect.y + m9_rect.h >= ball_rect.y &&
                    ball_rect.y + ball_rect.h >= m9_rect.y) {
                    x = false;
                }

                if (m9_rect.x + m9_rect.w >= ghost_rect.x &&
                    ghost_rect.x + ghost_rect.w >= m9_rect.x &&
                    m9_rect.y + m9_rect.h >= ghost_rect.y &&
                    ghost_rect.y + ghost_rect.h >= m9_rect.y) {
                    x = false;
                }
            }

            SDL_RenderCopy(renderer, ghost, NULL, &ghost_rect);
            SDL_RenderCopy(renderer, ex, NULL, &ex_rect);
            SDL_RenderCopy(renderer, laser, NULL, &laser_rect);
            if (movex > 0) direct = 1;
            else if (movex < 0) direct = 0;
            if (direct) SDL_RenderCopy(renderer, m9right, NULL, &m9_rect);
            else SDL_RenderCopy(renderer, m9left, NULL, &m9_rect);
            SDL_RenderPresent(renderer);

            dieuhuong(m9_rect, movex, movey);
            if (m9_rect.x + movex < SCREEN_WIDTH && m9_rect.x + movex >= 0) m9_rect.x = m9_rect.x + movex;
            if (m9_rect.y + movey < SCREEN_HEIGHT && m9_rect.y + movey >= 0) m9_rect.y = m9_rect.y + movey;

            if (ghost_rect.x > m9_rect.x) ghost_rect.x = ghost_rect.x - 2;
            else if (ghost_rect.x < m9_rect.x) ghost_rect.x = ghost_rect.x + 0,5;
            if (ghost_rect.y > m9_rect.y) ghost_rect.y = ghost_rect.y - 2;
            else if (ghost_rect.y < m9_rect.y) ghost_rect.y = ghost_rect.y + 0,5;

            cghost++;
            if (cghost == 250) {
                ghost_rect.x = SCREEN_WIDTH;
                ghost_rect.y = rand() % (SCREEN_HEIGHT - ghost_rect.h);
                cghost = 0;
            }

            ex_rect.x = ex_rect.x + i;
            laser_rect.w = laser_rect.w + li - 5;
            laser_rect.x = round(laser_rect.x - li - 5);
            ball_rect.y = ball_rect.y + i - 5;
            ball_rect.x = aball * ball_rect.y + bball - 5;
        }

        SDL_Texture* endg = loadtexture("endgame.png", renderer);
        SDL_RenderCopy(renderer, endg, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        SDL_Event e;
        while (true) {
            if (SDL_WaitEvent(&e) != 0)
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    cont = false;
                    break;
                }
                else if (e.key.keysym.sym == SDLK_r) {
                    break;
                }
            SDL_Delay(100);
        }
    }

    HuyTexture(background);
    HuyTexture(m9right);
    HuyTexture(ex);
    quitSDL(window, renderer);
    return 0;
}
