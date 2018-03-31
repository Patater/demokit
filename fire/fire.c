/*
 *  fire.c
 *  Patater Demo Kit
 *
 *  Created by Jaeden Amero on 2016-06-03.
 *  Copyright 2016. SPDX-License-Identifier: MIT
 *
 */

#include "firepal.h"
#include <SDL2/SDL.h>
#include <stdlib.h>


#define CAP_SPEED 1
#define PRINT_FPS 0
#define SHOW_COALS 0
#define WIDTH 320
#define HEIGHT 240


static uint8_t coal_range = 0x10;
static uint8_t coal_base = 0x20;
static uint8_t flame_range = 0xFF;
static uint8_t flame_base = 0xA0;
static uint8_t flame_chance = 0x05;
static uint8_t flame_width = 0x30;
static size_t coal_rows = 1;
static size_t fire_rows = 1;
#if CAP_SPEED
static size_t speed = 30;
#endif
static size_t width;
static size_t height;
static SDL_Window *window;
static SDL_Surface *screen;
static SDL_Surface *surface;
static uint8_t *pixels;
#if !SHOW_COALS
static size_t offset = 16;
#endif
static int gameover = 0;


void print_info()
{
    printf("coal_range: 0x%02X\n", coal_range);
    printf("coal_base: 0x%02X\n", coal_base);
    printf("flame_range: 0x%02X\n", flame_range);
    printf("flame_base: 0x%02X\n", flame_base);
    printf("flame_chance: 0x%02X\n", flame_chance);
    printf("flame_width: 0x%02X\n", flame_width);
}

void create_surface(void)
{
    surface = SDL_CreateRGBSurface(0, width, height, 8, 0, 0, 0, 0);

    SDL_SetPaletteColors(surface->format->palette, fire_palette, 0, 256);

    pixels = surface->pixels;

    /* Update the screen with the new surface. */
    SDL_BlitSurface(surface, NULL, screen, NULL);
}

void make_coals(void)
{
    size_t x;
    size_t y;
    y = height - 1;
    while (y > height - 1 - coal_rows)
    {
        for (x = 0; x < width; x++)
        {
            size_t coal = !coal_range ? 0 : (rand() % coal_range) + coal_base;
            coal = coal > 0xFF ? 0xFF : coal;
            pixels[y * surface->pitch + x] = coal;
        }
        --y;
    }

    while (y > height - 1 - coal_rows - fire_rows)
    {
        for (x = 0; x < width; x++)
        {
            if (rand() % 0x100 < flame_chance)
            {
                size_t fwidth = rand() % (flame_width + 1);
                size_t end = x + fwidth;
                end = end > width - 1 ? width - 1 : end;

                for (; x < end; x++)
                {
                    size_t flame = !flame_range ? 0 : (rand() % flame_range) + flame_base;
                    flame = flame > 0xFF ? 0xFF : flame;
                    pixels[y * surface->pitch + x] = flame;
                }
            }
            else
            {
                pixels[y * surface->pitch + x] = 0;
            }
        }
        --y;
    }
}

static void set_flame_pixel(size_t x, size_t y, size_t u, size_t d)

{
    size_t nw, w, sw, s, se, e, ne;
    size_t l, r;

    /* Wrap around at start and end columns. */
    l = x == 0 ? width - 1 : x - 1;
    r = x >= width - 1 ? 0 : x + 1;

    nw = pixels[u * surface->pitch + l];
    sw = pixels[d * surface->pitch + l];

    ne = pixels[u * surface->pitch + r];
    se = pixels[d * surface->pitch + r];

    w  = pixels[y * surface->pitch + l];
    e  = pixels[y * surface->pitch + r];
    s  = pixels[d * surface->pitch + x];

    pixels[u * surface->pitch + x] =
        ((nw + w + sw + ne + e + se + s) / 7) & 0xFF;
}

void make_flames(void)
{
    size_t x;
    size_t y;

    /* Start at bottom fire row. */
    for (y = height - 1 - coal_rows; y > 0; y--)
    {
        size_t u, d;

        /* Clamp at top and bottom rows. */
        u = y == 0 ? 0 : y - 1;
        d = y >= height - 1 ? height - 1 : y + 1;

        for (x = 0; x < width; ++x)
        {
            set_flame_pixel(x, y, u, d);
        }
    }
}

static void gameloop(void)
{
#if PRINT_FPS
    static size_t frames = 0;
    Uint32 start_time;
#endif
    static size_t heartbeat = 0;
    SDL_Event event;

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
                case SDLK_UP:
                    ++coal_range;
                    break;
                case SDLK_DOWN:
                    --coal_range;
                    break;
                case SDLK_LEFT:
                    --coal_base;
                    break;
                case SDLK_RIGHT:
                    ++coal_base;
                    break;

                case SDLK_INSERT:
                    ++flame_width;
                    break;
                case SDLK_DELETE:
                    --flame_width;
                    break;
                case SDLK_HOME:
                    break;
                case SDLK_END:
                    break;
                case SDLK_PAGEUP:
                    ++flame_chance;
                    break;
                case SDLK_PAGEDOWN:
                    --flame_chance;
                    break;

                case SDLK_KP_8:
                    ++flame_range;
                    break;
                case SDLK_KP_5:
                case SDLK_KP_2: /* fallthrough */
                    --flame_range;
                    break;
                case SDLK_KP_4:
                    --flame_base;
                    break;
                case SDLK_KP_6:
                    ++flame_base;
                    break;

                default:
                    break;
            }

            print_info();
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
        make_coals();
        make_flames();
        {
#if SHOW_COALS
        SDL_BlitSurface(surface, NULL, screen, NULL);
#else
        SDL_Rect dstrect;
        SDL_Rect srcrect;
        srcrect.x = 0;
        srcrect.y = 0;
        srcrect.w = width;
        srcrect.h = height - offset;
        dstrect.x = 0;
        dstrect.y = offset;
        dstrect.w = width;
        dstrect.h = height - offset;
        SDL_BlitSurface(surface, &srcrect, screen, &dstrect);
#endif
        SDL_UpdateWindowSurface(window);
        }
#if PRINT_FPS
        ++frames;
#endif
    }

    ++heartbeat;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    SDL_Init(SDL_INIT_VIDEO);
    width = WIDTH;
    height = HEIGHT;

    window = SDL_CreateWindow("Fire",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    screen = SDL_GetWindowSurface(window);

    create_surface();

    print_info();

#if PRINT_FPS
    start_time = SDL_GetTicks();
#endif
    while (!gameover)
    {
        gameloop();
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
