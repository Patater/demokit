/*
 *  plasmpal.c
 *  Patater Demo Kit
 *
 *  Created by Jaeden Amero on 2016-06-17.
 *  Copyright 2016. SPDX-License-Identifier: MIT
 *
 */

#include "plasmpal.h"
#include <SDL.h>

SDL_Color plasma_palette[256] = {
    { 0x00, 0x02, 0xFD, 0xFF},
    { 0x00, 0x06, 0xFE, 0xFF},
    { 0x00, 0x0C, 0xFE, 0xFF},
    { 0x00, 0x13, 0xFE, 0xFF},
    { 0x01, 0x18, 0xFE, 0xFF},
    { 0x02, 0x1E, 0xFE, 0xFF},
    { 0x01, 0x26, 0xFE, 0xFF},
    { 0x00, 0x2B, 0xFE, 0xFF},
    { 0x00, 0x30, 0xFE, 0xFF},
    { 0x00, 0x35, 0xFE, 0xFF},
    { 0x00, 0x3B, 0xFF, 0xFF},
    { 0x00, 0x41, 0xFE, 0xFF},
    { 0x00, 0x48, 0xFE, 0xFF},
    { 0x00, 0x4E, 0xFD, 0xFF},
    { 0x03, 0x54, 0xFD, 0xFF},
    { 0x02, 0x59, 0xFD, 0xFF},
    { 0x04, 0x60, 0xFF, 0xFF},
    { 0x02, 0x64, 0xFE, 0xFF},
    { 0x03, 0x6B, 0xFE, 0xFF},
    { 0x01, 0x72, 0xFE, 0xFF},
    { 0x01, 0x77, 0xFE, 0xFF},
    { 0x00, 0x7E, 0xFE, 0xFF},
    { 0x00, 0x84, 0xFD, 0xFF},
    { 0x00, 0x89, 0xFD, 0xFF},
    { 0x02, 0x8E, 0xFF, 0xFF},
    { 0x02, 0x93, 0xFF, 0xFF},
    { 0x01, 0x99, 0xFE, 0xFF},
    { 0x02, 0xA0, 0xFE, 0xFF},
    { 0x00, 0xA5, 0xFE, 0xFF},
    { 0x00, 0xAC, 0xFE, 0xFF},
    { 0x00, 0xB3, 0xFE, 0xFF},
    { 0x00, 0xB7, 0xFD, 0xFF},
    { 0x00, 0xBD, 0xFE, 0xFF},
    { 0x00, 0xC3, 0xFF, 0xFF},
    { 0x02, 0xCA, 0xFF, 0xFF},
    { 0x02, 0xD1, 0xFF, 0xFF},
    { 0x00, 0xD6, 0xFD, 0xFF},
    { 0x00, 0xDD, 0xFD, 0xFF},
    { 0x00, 0xE4, 0xFC, 0xFF},
    { 0x00, 0xEA, 0xFE, 0xFF},
    { 0x00, 0xEF, 0xFE, 0xFF},
    { 0x00, 0xF4, 0xFE, 0xFF},
    { 0x01, 0xFA, 0xFE, 0xFF},
    { 0x02, 0xFD, 0xFB, 0xFF},
    { 0x01, 0xFE, 0xF7, 0xFF},
    { 0x00, 0xFE, 0xF1, 0xFF},
    { 0x00, 0xFE, 0xEA, 0xFF},
    { 0x00, 0xFF, 0xE5, 0xFF},
    { 0x02, 0xFD, 0xE0, 0xFF},
    { 0x01, 0xFE, 0xD9, 0xFF},
    { 0x00, 0xFD, 0xD4, 0xFF},
    { 0x00, 0xFE, 0xCC, 0xFF},
    { 0x00, 0xFF, 0xC7, 0xFF},
    { 0x00, 0xFF, 0xC0, 0xFF},
    { 0x00, 0xFE, 0xBB, 0xFF},
    { 0x00, 0xFE, 0xB5, 0xFF},
    { 0x00, 0xFE, 0xAE, 0xFF},
    { 0x00, 0xFF, 0xA9, 0xFF},
    { 0x01, 0xFD, 0xA4, 0xFF},
    { 0x00, 0xFE, 0x9D, 0xFF},
    { 0x01, 0xFE, 0x97, 0xFF},
    { 0x00, 0xFF, 0x8F, 0xFF},
    { 0x00, 0xFE, 0x8A, 0xFF},
    { 0x00, 0xFF, 0x84, 0xFF},
    { 0x01, 0xFE, 0x7F, 0xFF},
    { 0x01, 0xFE, 0x79, 0xFF},
    { 0x00, 0xFD, 0x72, 0xFF},
    { 0x00, 0xFE, 0x6C, 0xFF},
    { 0x00, 0xFE, 0x67, 0xFF},
    { 0x00, 0xFF, 0x5F, 0xFF},
    { 0x00, 0xFE, 0x5A, 0xFF},
    { 0x00, 0xFE, 0x54, 0xFF},
    { 0x01, 0xFE, 0x50, 0xFF},
    { 0x00, 0xFE, 0x4A, 0xFF},
    { 0x01, 0xFC, 0x45, 0xFF},
    { 0x00, 0xFD, 0x3E, 0xFF},
    { 0x01, 0xFE, 0x39, 0xFF},
    { 0x00, 0xFE, 0x32, 0xFF},
    { 0x00, 0xFE, 0x2C, 0xFF},
    { 0x00, 0xFD, 0x26, 0xFF},
    { 0x00, 0xFE, 0x21, 0xFF},
    { 0x00, 0xFE, 0x1B, 0xFF},
    { 0x00, 0xFE, 0x14, 0xFF},
    { 0x00, 0xFD, 0x0D, 0xFF},
    { 0x00, 0xFD, 0x08, 0xFF},
    { 0x01, 0xFE, 0x03, 0xFF},
    { 0x05, 0xFF, 0x00, 0xFF},
    { 0x08, 0xFF, 0x00, 0xFF},
    { 0x11, 0xFF, 0x00, 0xFF},
    { 0x17, 0xFF, 0x00, 0xFF},
    { 0x1C, 0xFD, 0x01, 0xFF},
    { 0x24, 0xFE, 0x00, 0xFF},
    { 0x2A, 0xFE, 0x01, 0xFF},
    { 0x31, 0xFE, 0x01, 0xFF},
    { 0x32, 0xFF, 0x00, 0xFF},
    { 0x39, 0xFF, 0x00, 0xFF},
    { 0x3F, 0xFF, 0x00, 0xFF},
    { 0x44, 0xFE, 0x00, 0xFF},
    { 0x4A, 0xFE, 0x00, 0xFF},
    { 0x50, 0xFE, 0x00, 0xFF},
    { 0x58, 0xFE, 0x00, 0xFF},
    { 0x5E, 0xFE, 0x00, 0xFF},
    { 0x66, 0xFD, 0x00, 0xFF},
    { 0x6A, 0xFE, 0x00, 0xFF},
    { 0x6F, 0xFE, 0x01, 0xFF},
    { 0x72, 0xFE, 0x00, 0xFF},
    { 0x7A, 0xFE, 0x00, 0xFF},
    { 0x81, 0xFE, 0x01, 0xFF},
    { 0x89, 0xFE, 0x01, 0xFF},
    { 0x8E, 0xFD, 0x01, 0xFF},
    { 0x94, 0xFE, 0x01, 0xFF},
    { 0x98, 0xFE, 0x00, 0xFF},
    { 0x9E, 0xFE, 0x00, 0xFF},
    { 0xA2, 0xFE, 0x00, 0xFF},
    { 0xAA, 0xFD, 0x00, 0xFF},
    { 0xB0, 0xFD, 0x01, 0xFF},
    { 0xB6, 0xFE, 0x00, 0xFF},
    { 0xBC, 0xFD, 0x00, 0xFF},
    { 0xC4, 0xFD, 0x00, 0xFF},
    { 0xC7, 0xFD, 0x00, 0xFF},
    { 0xCF, 0xFE, 0x01, 0xFF},
    { 0xD2, 0xFE, 0x00, 0xFF},
    { 0xDA, 0xFF, 0x00, 0xFF},
    { 0xE0, 0xFE, 0x00, 0xFF},
    { 0xE6, 0xFE, 0x00, 0xFF},
    { 0xEC, 0xFE, 0x00, 0xFF},
    { 0xF4, 0xFF, 0x00, 0xFF},
    { 0xF8, 0xFE, 0x00, 0xFF},
    { 0xFC, 0xFE, 0x01, 0xFF},
    { 0xFD, 0xF9, 0x00, 0xFF},
    { 0xFE, 0xF2, 0x00, 0xFF},
    { 0xFE, 0xEC, 0x00, 0xFF},
    { 0xFF, 0xE5, 0x01, 0xFF},
    { 0xFF, 0xDF, 0x00, 0xFF},
    { 0xFF, 0xD8, 0x00, 0xFF},
    { 0xFE, 0xD3, 0x00, 0xFF},
    { 0xFE, 0xCD, 0x00, 0xFF},
    { 0xFC, 0xC8, 0x00, 0xFF},
    { 0xFD, 0xC3, 0x00, 0xFF},
    { 0xFC, 0xBC, 0x00, 0xFF},
    { 0xFF, 0xB6, 0x00, 0xFF},
    { 0xFF, 0xAF, 0x00, 0xFF},
    { 0xFF, 0xA8, 0x00, 0xFF},
    { 0xFF, 0xA4, 0x01, 0xFF},
    { 0xFD, 0x9F, 0x00, 0xFF},
    { 0xFC, 0x9A, 0x00, 0xFF},
    { 0xFB, 0x93, 0x00, 0xFF},
    { 0xFC, 0x8E, 0x00, 0xFF},
    { 0xFF, 0x86, 0x01, 0xFF},
    { 0xFF, 0x81, 0x01, 0xFF},
    { 0xFF, 0x7A, 0x01, 0xFF},
    { 0xFE, 0x75, 0x01, 0xFF},
    { 0xFD, 0x70, 0x00, 0xFF},
    { 0xFC, 0x6B, 0x00, 0xFF},
    { 0xFD, 0x65, 0x00, 0xFF},
    { 0xFC, 0x5F, 0x00, 0xFF},
    { 0xFF, 0x58, 0x01, 0xFF},
    { 0xFE, 0x52, 0x00, 0xFF},
    { 0xFF, 0x4B, 0x00, 0xFF},
    { 0xFF, 0x47, 0x01, 0xFF},
    { 0xFF, 0x41, 0x00, 0xFF},
    { 0xFF, 0x3C, 0x00, 0xFF},
    { 0xFC, 0x34, 0x00, 0xFF},
    { 0xFD, 0x2E, 0x00, 0xFF},
    { 0xFF, 0x28, 0x01, 0xFF},
    { 0xFF, 0x22, 0x02, 0xFF},
    { 0xFF, 0x1A, 0x02, 0xFF},
    { 0xFF, 0x14, 0x00, 0xFF},
    { 0xFF, 0x0F, 0x00, 0xFF},
    { 0xFF, 0x0A, 0x00, 0xFF},
    { 0xFD, 0x04, 0x00, 0xFF},
    { 0xFC, 0x01, 0x02, 0xFF},
    { 0xFD, 0x00, 0x09, 0xFF},
    { 0xFF, 0x00, 0x0D, 0xFF},
    { 0xFF, 0x00, 0x14, 0xFF},
    { 0xFE, 0x00, 0x17, 0xFF},
    { 0xFC, 0x00, 0x1F, 0xFF},
    { 0xFD, 0x01, 0x24, 0xFF},
    { 0xFF, 0x01, 0x2C, 0xFF},
    { 0xFF, 0x00, 0x32, 0xFF},
    { 0xFF, 0x00, 0x38, 0xFF},
    { 0xFE, 0x00, 0x3D, 0xFF},
    { 0xFF, 0x00, 0x46, 0xFF},
    { 0xFF, 0x00, 0x49, 0xFF},
    { 0xFF, 0x00, 0x50, 0xFF},
    { 0xFC, 0x00, 0x53, 0xFF},
    { 0xFD, 0x00, 0x5A, 0xFF},
    { 0xFC, 0x00, 0x60, 0xFF},
    { 0xFF, 0x00, 0x67, 0xFF},
    { 0xFF, 0x00, 0x6E, 0xFF},
    { 0xFE, 0x00, 0x74, 0xFF},
    { 0xFE, 0x00, 0x78, 0xFF},
    { 0xFD, 0x00, 0x81, 0xFF},
    { 0xFC, 0x00, 0x84, 0xFF},
    { 0xFE, 0x01, 0x8C, 0xFF},
    { 0xFF, 0x00, 0x91, 0xFF},
    { 0xFF, 0x00, 0x97, 0xFF},
    { 0xFE, 0x00, 0x9C, 0xFF},
    { 0xFF, 0x00, 0xA5, 0xFF},
    { 0xFD, 0x00, 0xA9, 0xFF},
    { 0xFF, 0x00, 0xAE, 0xFF},
    { 0xFD, 0x01, 0xB2, 0xFF},
    { 0xFF, 0x01, 0xBA, 0xFF},
    { 0xFE, 0x01, 0xC0, 0xFF},
    { 0xFF, 0x00, 0xC5, 0xFF},
    { 0xFF, 0x00, 0xCC, 0xFF},
    { 0xFF, 0x00, 0xD2, 0xFF},
    { 0xFF, 0x01, 0xD7, 0xFF},
    { 0xFE, 0x00, 0xDD, 0xFF},
    { 0xFF, 0x01, 0xE2, 0xFF},
    { 0xFF, 0x00, 0xEA, 0xFF},
    { 0xFF, 0x01, 0xF1, 0xFF},
    { 0xFF, 0x01, 0xF6, 0xFF},
    { 0xFD, 0x00, 0xFB, 0xFF},
    { 0xF9, 0x00, 0xFE, 0xFF},
    { 0xF4, 0x00, 0xFF, 0xFF},
    { 0xEF, 0x00, 0xFE, 0xFF},
    { 0xE7, 0x00, 0xFD, 0xFF},
    { 0xE2, 0x01, 0xFD, 0xFF},
    { 0xDA, 0x01, 0xFC, 0xFF},
    { 0xD4, 0x00, 0xFD, 0xFF},
    { 0xCD, 0x01, 0xFC, 0xFF},
    { 0xCC, 0x00, 0xFF, 0xFF},
    { 0xC5, 0x00, 0xFE, 0xFF},
    { 0xBE, 0x00, 0xFF, 0xFF},
    { 0xB8, 0x00, 0xFE, 0xFF},
    { 0xB3, 0x01, 0xFE, 0xFF},
    { 0xAC, 0x01, 0xFD, 0xFF},
    { 0xA6, 0x01, 0xFD, 0xFF},
    { 0x9E, 0x01, 0xFC, 0xFF},
    { 0x9A, 0x01, 0xFE, 0xFF},
    { 0x94, 0x01, 0xFD, 0xFF},
    { 0x8F, 0x00, 0xFF, 0xFF},
    { 0x8A, 0x00, 0xFF, 0xFF},
    { 0x86, 0x00, 0xFF, 0xFF},
    { 0x7D, 0x00, 0xFE, 0xFF},
    { 0x77, 0x00, 0xFE, 0xFF},
    { 0x72, 0x00, 0xFE, 0xFF},
    { 0x6B, 0x00, 0xFD, 0xFF},
    { 0x66, 0x01, 0xFD, 0xFF},
    { 0x61, 0x00, 0xFE, 0xFF},
    { 0x5A, 0x00, 0xFE, 0xFF},
    { 0x55, 0x00, 0xFD, 0xFF},
    { 0x4E, 0x01, 0xFD, 0xFF},
    { 0x48, 0x00, 0xFE, 0xFF},
    { 0x40, 0x00, 0xFD, 0xFF},
    { 0x3B, 0x00, 0xFD, 0xFF},
    { 0x36, 0x00, 0xFD, 0xFF},
    { 0x2F, 0x00, 0xFF, 0xFF},
    { 0x2A, 0x00, 0xFF, 0xFF},
    { 0x25, 0x00, 0xFF, 0xFF},
    { 0x1E, 0x00, 0xFF, 0xFF},
    { 0x18, 0x00, 0xFF, 0xFF},
    { 0x10, 0x00, 0xFF, 0xFF},
    { 0x0B, 0x00, 0xFF, 0xFF},
    { 0x08, 0x00, 0xFF, 0xFF},
};
