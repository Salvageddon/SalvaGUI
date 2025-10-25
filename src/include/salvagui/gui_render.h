#pragma once

#include "gui_window.h"

void GUI_setPixel(GUI_window * win, int x, int y, Uint32 color);
void GUI_setPixelOnSur(SDL_Surface * sur, int x, int y, Uint32 color);
Uint32 GUI_getPixel(GUI_window * win, int x, int y);
Uint32 GUI_getPixelFromSur(SDL_Surface * sur, int x, int y);
void GUI_updatePixels(GUI_window * win);
void GUI_bakeGUI(GUI_window * win);
void GUI_renderGUI(GUI_window * win);
void GUI_refreshScreen(GUI_window * win);