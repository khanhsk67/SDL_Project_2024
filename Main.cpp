#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "SDL_func.hpp"

using namespace std;

SDL_Renderer* renderer;
SDL_Window* window;

int movex, movey = 0;


int main(int argc, char* argv[])
{
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
    //ball_rect.y = a*ball_rect.y + b;
    SDL_Rect ghost_rect;



    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, m9right, NULL, &m9_rect);

    bool cont = true;

    while (cont)
    {
        bool direct = 1;
        float i = 5;
        int li = 15;
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
        ex_rect.y = rand() % (SCREEN_HEIGHT - 100) + 60;
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
        float aball = 1;
        int bball = 0;


        ghost_rect.x = SCREEN_WIDTH;
        ghost_rect.y = 0;
        ghost_rect.h = 45;
        ghost_rect.w = 45;
        float aghost = 1;
        int bghost = 0;
        int cghost = 0;

        while (x)
        {
            SDL_RenderCopy(renderer, background, NULL, NULL);

            if (bi >= 1 && bi < 4)
            {
                SDL_RenderCopy(renderer, ball1, NULL, &ball_rect);
                bi++;
            }
            else if (bi >= 4 && bi < 7)
            {
                SDL_RenderCopy(renderer, ball2, NULL, &ball_rect);
                bi++;
            }
            else if (bi >= 7 && bi < 10)
            {
                SDL_RenderCopy(renderer, ball3, NULL, &ball_rect);
                bi++;
            }
            else if (bi >= 10 && bi < 13)
            {
                SDL_RenderCopy(renderer, ball4, NULL, &ball_rect);
                bi++;
            }
            else bi = 1;







            // excalibur
            if (ex_rect.x >= SCREEN_WIDTH)
            {
                cex = 1;
                ex_rect.x = 0;


                ex_rect.y = rand() % (SCREEN_HEIGHT - ex_rect.h);
                cex = 0;
                i = i + 0.005;
            }


            // laser beam
            if (laser_rect.w >= SCREEN_WIDTH + 20)
            {
                claser = 1;
                laser_rect.w = 25;
                laser_rect.x = SCREEN_WIDTH;

                laser_rect.y = rand() % (SCREEN_HEIGHT - laser_rect.h);
                claser = 0;

            }




            //Ball
            if (ball_rect.x <0 || ball_rect.y >= SCREEN_HEIGHT || ball_rect.x > SCREEN_WIDTH || ball_rect.y < 0)
            {
                ball_rect.x = rand() % (SCREEN_WIDTH - ball_rect.w);
                if (ball_rect.x > SCREEN_WIDTH / 2)
                {
                    cball = 0;
                }
                else
                {
                    cball = 1;
                }
                ball_rect.y = 0;


                bball = ball_rect.x;

                aball = 1.0 * (m9_rect.x - bball) / (m9_rect.y + 300);
                if (aball > 1) aball = 1;
                if (aball < -1) aball = -1;

            }





            //Dead ex
            if (m9_rect.x + m9_rect.w >= ex_rect.x &&
                ex_rect.x + ex_rect.w >= m9_rect.x &&
                m9_rect.y + m9_rect.h >= ex_rect.y &&
                ex_rect.y + ex_rect.h >= m9_rect.y)
            {
                x = false;
            }


            //Dead laser
            if (m9_rect.x + m9_rect.w >= laser_rect.x &&
                laser_rect.x + laser_rect.w >= m9_rect.x &&
                m9_rect.y + m9_rect.h >= laser_rect.y &&
                laser_rect.y + laser_rect.h >= m9_rect.y)
            {
                x = false;
            }


            //Dead ex
            if (m9_rect.x + m9_rect.w >= ex_rect.x &&
                ex_rect.x + ex_rect.w >= m9_rect.x &&
                m9_rect.y + m9_rect.h >= ex_rect.y &&
                ex_rect.y + ex_rect.h >= m9_rect.y)
            {
                x = false;
            }


            //Dead ball
            if (m9_rect.x + m9_rect.w >= ball_rect.x &&
                ball_rect.x + ball_rect.w >= m9_rect.x &&
                m9_rect.y + m9_rect.h >= ball_rect.y &&
                ball_rect.y + ball_rect.h >= m9_rect.y)
            {
                x = false;
            }



            if (m9_rect.x + m9_rect.w >= ghost_rect.x &&
                ghost_rect.x + ghost_rect.w >= m9_rect.x &&
                m9_rect.y + m9_rect.h >= ghost_rect.y &&
                ghost_rect.y + ghost_rect.h >= m9_rect.y)
            {
                x = false;
            }



            SDL_RenderCopy(renderer, ghost, NULL, &ghost_rect);
            SDL_RenderCopy(renderer, ex, NULL, &ex_rect);
            SDL_RenderCopy(renderer, laser, NULL, &laser_rect);
            if (movex > 0) direct = 1;
            else if (movex < 0) direct = 0;
            if (direct) SDL_RenderCopy(renderer, m9right, NULL, &m9_rect);
            else SDL_RenderCopy(renderer, m9left, NULL, &m9_rect);
            SDL_RenderPresent(renderer);




    HuyTexture(background);
    HuyTexture(m9right);
    HuyTexture(ex);
    quitSDL(window, renderer);
    return 0;


}
