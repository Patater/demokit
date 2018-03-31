/*
 *  plasma.c
 *  Patater Demo Kit
 *
 *  Created by Jaeden Amero on 2016-06-17.
 *  Copyright 2016. SPDX-License-Identifier: MIT
 *
 */

#include "plasmpal.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>

#define CAP_SPEED 1
#define WIDTH 320
#define HEIGHT 240
#define PRINT_FPS 0

#if CAP_SPEED
static size_t speed = 30;
#endif

static size_t width;
static size_t height;
static SDL_Surface *screen;
static SDL_Surface *surface;
static uint8_t *pixels;

void create_surface(void)
{
    surface = SDL_CreateRGBSurface(0, width, height, 8, 0, 0, 0, 0);

    SDL_SetPaletteColors(surface->format->palette, plasma_palette, 0, 256);

    pixels = surface->pixels;

    /* Update the screen with the new surface. */
    SDL_BlitSurface(surface, NULL, screen, NULL);
}

static void rotate_palette(void)
{
    SDL_Color color;
    size_t i;

    color = plasma_palette[0];
    for (i = 0; i < 256 - 1; i++)
    {
        plasma_palette[i] = plasma_palette[i + 1];
    }
    plasma_palette[i] = color;
}

static double dist(double x0, double y0, double x1, double y1)
{
    return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}

static void initialize_plasma(void)
{
    size_t x;
    size_t y;

    double p1x = 0.75;
    double p1y = 0.75;
    double p2x = 0.25;
    double p2y = 0.25;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            double q1 = dist(x, y, width * p1x, height * p1y);
            double q2 = dist(x, y, width * p2x * 0.5, height * p2y);
            double q3 = dist(x, y, width * p1x * 1.3, height * p1y);
            double q4 = dist(x, y, width * p2x * 1.5, height * p2y * 1.2);

            pixels[y * surface->pitch + x] =
                (4 + (sin(q1 / 8.0) + sin(q2 / 8.0) +
                      sin(q3 / 8.0) + sin(q4 / 8.0))) * 32;
        }
    }

    SDL_BlitSurface(surface, NULL, screen, NULL);
}

int main(int argc, char *argv[]) {
    static size_t heartbeat = 0;
#if PRINT_FPS
    static size_t frames = 0;
    Uint32 start_time;
#endif
    SDL_Event event;
    SDL_Window *window;
    int gameover = 0;

    (void)argc;
    (void)argv;

    SDL_Init(SDL_INIT_VIDEO);
    width = WIDTH;
    height = HEIGHT;

    window = SDL_CreateWindow("Plasma",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    screen = SDL_GetWindowSurface(window);

    create_surface();

    initialize_plasma();

#if PRINT_FPS
    start_time = SDL_GetTicks();
#endif
    while (!gameover)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameover = 1;
            }
            else if (event.type == SDL_WINDOWEVENT)
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        width = event.window.data1;
                        height = event.window.data2;

                        SDL_FreeSurface(screen);
                        screen = SDL_GetWindowSurface(window);

                        SDL_FreeSurface(surface);
                        create_surface();

                        initialize_plasma();

                        break;
                    default:
                        break;
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        gameover = 1;
                        break;

                    default:
                        break;
                }
            }
        }

#if PRINT_FPS
        if (heartbeat % 1000 == 0)
        {
            float fps = (frames / (float)(SDL_GetTicks() - start_time)) * 1000;
            printf("FPS: %f\n", fps);
        }
#endif

#if CAP_SPEED
        if (heartbeat % speed == 0)
#endif
        {
            rotate_palette();
            SDL_SetPaletteColors(surface->format->palette, plasma_palette, 0, 256);

            /* Copying the surface to the screen is unfortunately needed,
             * because real paletted hardware is hard to come by these days. */
            SDL_BlitSurface(surface, NULL, screen, NULL);

            SDL_UpdateWindowSurface(window);
#if PRINT_FPS
            ++frames;
#endif
        }

        ++heartbeat;
#if CAP_SPEED
        SDL_Delay(1);
#endif
    }

    SDL_FreeSurface(screen);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
