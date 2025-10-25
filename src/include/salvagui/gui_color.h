#pragma once

#include "gui_window.h"

/*
    RGB color data.
*/
typedef struct{
    Uint8 r, g, b;
} GUI_colorRGB;

/*
    RGBA color data.
*/
typedef struct{
    Uint8 r, g, b, a;
} GUI_colorRGBA;

/*
    Converts hex code into GUI_colorRGB.

    \param color Color in hex code.
    \param format The color format.

    \returns Specified color in RGB data.
*/
GUI_colorRGB GUI_getColorRGB(Uint32 color, SDL_PixelFormat format);

/*
    Converts hex code into GUI_colorRGBA.

    \param color Color in hex code.
    \param format The color format.

    \returns Specified color in RGBA data.
*/
GUI_colorRGBA GUI_getColorRGBA(Uint32 color, SDL_PixelFormat format);

/*
    Converts GUI_colorRGB into hex code.

    \param color Color in GUI_colorRGB.
    \param format The color format.

    \returns Specified color in hex code.
*/
Uint32 GUI_mapColorRGB(GUI_colorRGB color, SDL_PixelFormat format);

/*
    Converts GUI_colorRGBA into hex code.

    \param color Color in GUI_colorRGBA.
    \param format The color format.

    \returns Specified color in hex code.
*/
Uint32 GUI_mapColorRGBA(GUI_colorRGBA color, SDL_PixelFormat format);