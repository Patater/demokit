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

/* Texture dimensions must be powers of 2 for wrap around to work well. */
#define TEX_WIDTH 256
#define TEX_HEIGHT 256

#define CAP_SPEED 1
#define WIDTH 320
#define HEIGHT 240
#define PRINT_FPS 0

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const float spin = TEX_WIDTH * 0.002f;
static const float zoom = TEX_HEIGHT * 0.025f;
static const float x_speed = 1 / 20.0f * 0.25f;
static const float y_speed = 1 / 30.0f * 0.25f;

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
static SDL_Color palette[256];
static size_t texture[TEX_WIDTH * TEX_HEIGHT];
static int *angle_table;
static size_t *distance_table;
static uint8_t *pixels;
static int gameover = 0;


static void init_texture(void)
{
    size_t x;
    size_t y;

    for (y = 0; y < TEX_HEIGHT; y++)
    {
        for (x = 0; x < TEX_WIDTH; x++)
        {
            texture[y * TEX_WIDTH + x] = (x ^ y) % 256;
        }
    }
}

static double dist(double x0, double y0, double x1, double y1)
{
    return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}

static void create_transforms(void)
{
    size_t x;
    size_t y;

    free(angle_table);
    free(distance_table);
    angle_table = malloc(sizeof(*angle_table) * width * height * 4);
    distance_table = malloc(sizeof(*distance_table) * width * height * 4);

    for (y = 0; y < height * 2; y++)
    {
        for (x = 0; x < width * 2; x++)
        {
            int angle;
            double angle_prescale;
            size_t distance;
            double dist_prescale;
            static const double ratio = 32.0;

            angle_prescale = atan2((double)y - height, (double)x - width);
            angle = 0.5 * TEX_WIDTH * angle_prescale / M_PI;

            dist_prescale = dist(x, y, width, height);
            distance = dist_prescale ?
                           (size_t)(ratio * TEX_HEIGHT /
                               dist_prescale) % TEX_HEIGHT
                           : 0;

            angle_table[y * width * 2 + x] = angle;
            distance_table[y * width * 2 + x] = distance;
        }
    }
}

static SDL_Color hsv2rgb(unsigned int h, unsigned int s, unsigned int v)
{
    SDL_Color color;
    const unsigned int hi = h / (255 / 6 + 1);
    const unsigned int hj = (h - hi * (255 / 6 + 1)) * 6;
    const unsigned int p = v * (255 - s) / 255;
    const unsigned int q = v * (255 - (s * hj) / 255) / 255;
    const unsigned int t = v * (255 - (s * (255 - hj)) / 255) / 255;

    switch (hi)
    {
        case 0:
            color.r = v;
            color.g = t;
            color.b = p;
            break;
        case 1:
            color.r = q;
            color.g = v;
            color.b = p;
            break;
        case 2:
            color.r = p;
            color.g = v;
            color.b = t;
            break;
        case 3:
            color.r = p;
            color.g = q;
            color.b = v;
            break;
        case 4:
            color.r = t;
            color.g = p;
            color.b = v;
            break;
        case 5:
            color.r = v;
            color.g = p;
            color.b = q;
            break;
        default:
            color.r = 0;
            color.g = 0;
            color.b = 0;
            break;
    }

    color.a = 0xFF;

    return color;
}

static void init_palette(void)
{
    size_t i;

    /* Make a rainbow palette. */
    for (i = 0; i < 256; i++)
    {
        palette[i] = hsv2rgb(i, 255, 255);
    }
}

static void plot_pixel(size_t x, size_t y, size_t color)
{
    pixels[y * surface->pitch + x] = color;
}

static void render(size_t frame)
{
    const size_t a_offset = spin * frame;
    const size_t d_offset = zoom * frame;
    const size_t x_look = width / 2 + (width / 2) * sin(frame * x_speed);
    const size_t y_look = height / 2 + (height / 2) * sin(frame * y_speed);
    size_t x;
    size_t y;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            size_t u;
            size_t v;
            size_t color;
            const size_t xi = x + x_look;
            const size_t yi = y + y_look;

            u = (angle_table[yi * width * 2 + xi] + a_offset) % TEX_WIDTH;
            v = (distance_table[yi * width * 2 + xi] + d_offset) % TEX_HEIGHT;

            color = texture[v * TEX_WIDTH + u];
            plot_pixel(x, y, color);
        }
    }
}

static void create_surface(void)
{
    surface = SDL_CreateRGBSurface(0, width, height, 8, 0, 0, 0, 0);

    SDL_SetPaletteColors(surface->format->palette, palette, 0, 256);

    pixels = surface->pixels;

    /* Update the screen with the new surface. */
    SDL_BlitSurface(surface, NULL, screen, NULL);
}

static void gameloop(void)
{
    static size_t heartbeat = 0;
    static size_t frames = 0;

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
                    create_transforms();

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
        render(frames);

        /* Copy the surface to the screen, which transforms from 256-color
         * indexed to whatever the screen actually is. */
        SDL_BlitSurface(surface, NULL, screen, NULL);

        SDL_UpdateWindowSurface(window);
        ++frames;
    }

    ++heartbeat;
}

int main(int argc, char *argv[]) {
#if PRINT_FPS
    Uint32 start_time;
#endif

    (void)argc;
    (void)argv;

    SDL_Init(SDL_INIT_VIDEO);
    width = WIDTH;
    height = HEIGHT;

    window = SDL_CreateWindow("Tunnel",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    screen = SDL_GetWindowSurface(window);

    init_palette();
    init_texture();
    create_surface();
    create_transforms();

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
