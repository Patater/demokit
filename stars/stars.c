/*
 *  stars.c
 *  Patater Demo Kit
 *
 *  Created by Jaeden Amero on 2016-06-19.
 *  Copyright 2016. SPDX-License-Identifier: MIT
 *
 */

#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define NUM_STARS 1024
#define ERASE_OLD_STARS 1
#define CAP_SPEED 1
#define WIDTH 320
#define HEIGHT 240
#define PRINT_FPS 0
#define NEED_HEARTBEAT (PRINT_FPS || (CAP_SPEED && !__EMSCRIPTEN__))

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const float star_speed = 0.025f;
static const float z_start = -8.0f;
static const float r_range = 100000.0f;

#ifndef __EMSCRIPTEN__
#if CAP_SPEED
static size_t speed = 30;
#endif
#endif

static size_t width;
static size_t height;
static SDL_Window *window;
static SDL_Surface *screen;
static SDL_Surface *surface;
static SDL_Color star_palette[256];
static uint8_t *pixels;
static int gameover = 0;

struct star {
    float x;
    float y;
    float z;
    size_t initial_color;
};

struct star stars[NUM_STARS];

static void init_star(struct star *star)
{
    /* Make a disc of stars. */
    const float t = ((float)rand() / (float)RAND_MAX) * (2.0f * M_PI);
    const float r = r_range * ((float)rand() / (float)RAND_MAX);
    star->x = r * cos(t);                 /* [-r_range, r_range] */
    star->y = r * sin(t);                 /* [-r_range, r_range] */
    star->z = z_start;


    /* [0, 255] */
    star->initial_color = (1.0f - ((float)rand() / (float)RAND_MAX) * 0.75f) * 255.0f;
    star->initial_color = star->initial_color > 255 ? 255
                                                    : star->initial_color;
}

static size_t star_color(struct star *star)
{
    /* Make star more dim when far away. */
    size_t color = (star->initial_color / 255.0f)
                   * (1.0f - fabs(star->z / z_start)) * 255;
    color = color > 255 ? 255 : color; /* [0, 255] */

    return color;
}

static void plot_pixel(size_t x, size_t y, size_t color)
{
    pixels[y * surface->pitch + x] = color;
}

static int clip_pixel(size_t x, size_t y)
{
    /* Clip if the point is not on the screen */
    return x >= width || y >= height;
}

static void render_stars(void)
{
    size_t i;

    for (i = 0; i < NUM_STARS; i++)
    {
        size_t x;
        size_t y;
        float widthf = width;
        float heightf = height;
        float x_pre;
        float y_pre;

        /* Old position */
        x_pre = stars[i].x / stars[i].z + widthf / 2.0f;
        x = x_pre >= 0.0f ? x_pre : width; /* Draw off screen if negative. */
        y_pre = stars[i].y / stars[i].z + heightf / 2.0f;
        y = y_pre >= 0.0f ? y_pre : height; /* Draw off screen if negative. */

        /* If star is out of sight: */
        if (clip_pixel(x, y))
        {
            /* Make it into a new star. */
            init_star(&stars[i]);
            continue;
        }

        /* Erase the previously drawn star. */
#if ERASE_OLD_STARS
        plot_pixel(x, y, 0);
#endif

        /* Move star closer. */
        stars[i].z += star_speed;

        /* New position */
        x_pre = stars[i].x / stars[i].z + widthf / 2.0f;
        x = x_pre >= 0.0f ? x_pre : width; /* Draw off screen if negative. */
        y_pre = stars[i].y / stars[i].z + heightf / 2.0f;
        y = y_pre >= 0.0f ? y_pre : height; /* Draw off screen if negative. */

        /* If star is out of sight: */
        if (clip_pixel(x, y))
        {
            /* Make it into a new star. */
            init_star(&stars[i]);
        }
        else
        {
            /* Draw the new star. */
            plot_pixel(x, y, star_color(&stars[i]));
        }
    }
}

static void init_stars(void)
{
    size_t i;

    for (i = 0; i < NUM_STARS; i++)
    {
        init_star(&stars[i]);
    }
}

static void init_star_palette(void)
{
    size_t i;

    /* Make a grayscale palette. */
    for (i = 0; i < 256; i++)
    {
        star_palette[i].r = i;
        star_palette[i].g = i;
        star_palette[i].b = i;
        star_palette[i].a = 0xFF;
    }
}

static void create_surface(void)
{
    surface = SDL_CreateRGBSurface(0, width, height, 8, 0, 0, 0, 0);

    SDL_SetPaletteColors(surface->format->palette, star_palette, 0, 256);

    pixels = surface->pixels;

    /* Update the screen with the new surface. */
    SDL_BlitSurface(surface, NULL, screen, NULL);
}

static void gameloop(void)
{
#if NEED_HEARTBEAT
    static size_t heartbeat = 0;
#endif
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

                    init_stars();

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

#ifndef __EMSCRIPTEN__
#if CAP_SPEED
    if (heartbeat % speed == 0)
#endif
#endif
    {
        render_stars();

        /* Copy the surface to the screen, which transforms from 256-color
         * indexed to whatever the screen actually is. */
        SDL_BlitSurface(surface, NULL, screen, NULL);

        SDL_UpdateWindowSurface(window);
#if PRINT_FPS
        ++frames;
#endif
    }

#if NEED_HEARTBEAT
    ++heartbeat;
#endif
}

int main(int argc, char *argv[])
{
#if PRINT_FPS
    static size_t frames = 0;
    Uint32 start_time;
#endif

    (void)argc;
    (void)argv;

    SDL_Init(SDL_INIT_VIDEO);
    width = WIDTH;
    height = HEIGHT;

    window = SDL_CreateWindow("Stars",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    screen = SDL_GetWindowSurface(window);

    init_star_palette();

    create_surface();

    init_stars();

#if PRINT_FPS
    start_time = SDL_GetTicks();
#endif
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(gameloop, 0, 1);
#else
    while (!gameover)
    {
        gameloop();
#if CAP_SPEED
        SDL_Delay(1);
#endif
    }
#endif

    SDL_FreeSurface(screen);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
