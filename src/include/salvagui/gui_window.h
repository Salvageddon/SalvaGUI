#pragma once

#include <SDL.h>
#include "gui_controls.h"

/* 
    SalvaGUI window. 
    
    You can access SDL members from it.

    Use GUI_createWindow() to initialize and GUI_destroyWindow to 
    safely free the window.
*/
typedef struct{
    GUI_context * gui; /* GUI base. */
    
    SDL_Window * win; /* Stores window data. */
    SDL_Surface * sur; /* Stores window pixels. */

    int w; /* Width of the window. */
    int h; /* Height of the window. */
} GUI_window;

/* 
    Base element of the GUI tree. 
    
    Use GUI_createGUI() to initialize and GUI_destroyGUI() to
    safely free all GUI controls. It's protected.
*/
typedef struct GUI_BASE GUI_base;

/* 
    Create GUI_window.

    To free it call GUI_destroyWindow().

    \param win GUI_window to be initialized
    \param title Title of the window.
    \param w Width of the window.
    \param h Height of the window.

    \returns 1 on error or 0 on success
*/
int GUI_createWindow(GUI_window * win, char * title, int w, int h, Uint32 flags);

/*
    Free GUI_window.

    \param win GUI_window to be freed.
*/
void GUI_destroyWindow(GUI_window * win);

/*
    Create GUI base for GUI_window

    \param win GUI_window to have base initialized

    \returns 1 on error or 0 on success
*/
int GUI_createGUI(GUI_window * win);

/*
    Free GUI base.

    \param win GUI_window to have GUI base freed.
*/
void GUI_destroyGUI(GUI_window * win);