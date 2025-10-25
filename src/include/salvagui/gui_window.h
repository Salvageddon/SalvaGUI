#pragma once

#include <SDL.h>
#include "gui_controls.h"

typedef struct{
    GUI_context * gui; 
    
    SDL_Window * win; 
    SDL_Surface * sur; 

    int w; 
    int h; 
} GUI_window;

typedef struct GUI_BASE GUI_base;

int GUI_createWindow(GUI_window * win, char * title, int w, int h, Uint32 flags);
void GUI_destroyWindow(GUI_window * win);
int GUI_createGUI(GUI_window * win);
void GUI_destroyGUI(GUI_window * win);