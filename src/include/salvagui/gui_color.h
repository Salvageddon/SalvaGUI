#pragma once

#include "gui_window.h"

typedef struct{
    Uint8 r, g, b;
} colorRGB;

typedef struct{
    Uint8 r, g, b, a;
} colorRGBA;

colorRGB GUI_getColorRGB(Uint32 color, SDL_PixelFormat format);
colorRGBA GUI_getColorRGBA(Uint32 color, SDL_PixelFormat format);
Uint32 GUI_mapColorRGB(colorRGB color, SDL_PixelFormat format);
Uint32 GUI_mapColorRGBA(colorRGBA color, SDL_PixelFormat format);