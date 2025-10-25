#pragma once

#include "gui_window.h"

/* 
    Set a pixel at specified coordinates on GUI_window.

    \param win GUI_window to have pixel changed.
    \param x The x coordinate of pixel.
    \param y The y coordinate of pixel.
    \param color The new color of pixel.
*/
void GUI_setPixel(GUI_window * win, int x, int y, Uint32 color);

/* 
    Set a pixel at specified coordinates on SDL_Surface.

    \param win SDL_Surface to have pixel changed.
    \param x The x coordinate of pixel.
    \param y The y coordinate of pixel.
    \param color The new color of pixel.
*/
void GUI_setPixelOnSur(SDL_Surface * sur, int x, int y, Uint32 color);

/* 
    Get a pixel from specified coordinates on GUI_window.

    \param win GUI_window to have pixel returned.
    \param x The x coordinate of pixel.
    \param y The y coordinate of pixel.
    
    \returns Color of specified pixel.
*/
Uint32 GUI_getPixel(GUI_window * win, int x, int y);

/* 
    Get a pixel from specified coordinates on SDL_Surface.

    \param win SDL_Surface to have pixel returned.
    \param x The x coordinate of pixel.
    \param y The y coordinate of pixel.
    
    \returns Color of specified pixel.
*/
Uint32 GUI_getPixelFromSur(SDL_Surface * sur, int x, int y);

/*
    Update GUI_window pixels to show changes on screen.

    \param win GUI_window to be updated.
*/
void GUI_updatePixels(GUI_window * win);

/*
    Calculate all necessary data for GUI controls rendering.

    \param win GUI_window to have control data calculated.
*/
void GUI_bakeGUI(GUI_window * win);

/*
    Render GUI controls on screen.
    Before calling this function you need to call GUI_bakeGUI().

    \param win GUI_window to have controls rendered.
*/
void GUI_renderGUI(GUI_window * win);

/*
    Refreshes the GUI_window, which means all pixels are being set to black.

    \param win GUI_window to have screen refreshed.
*/
void GUI_refreshScreen(GUI_window * win);