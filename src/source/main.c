#include <stdio.h>
#include "../include/salvagui/gui.h"

GUI_window win;

int main(int argc, char * argv[]){
    GUI_initSDL(SDL_INIT_VIDEO);
    GUI_createWindow(&win, "SalvaGUI", 1280, 720, 0);

    GUI_createGUI(&win);

    GUI_button * btn = GUI_createButton(win.gui, NULL);

    btn->style.backgroundColor = 0x00FFFF;
    btn->rect.w = 100;
    btn->rect.h = 150;

    GUI_bakeControls(&win);

    int running = 1;

    while(running){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_EVENT_QUIT:
                    running = 0;
                break;
            }
        }

        GUI_renderControls(&win);
        GUI_updatePixels(&win);
    }

    GUI_destroyWindow(&win);
    SDL_Quit();

    return 0;
}