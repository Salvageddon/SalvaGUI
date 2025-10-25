/*
    Main function for testing the SalvaGUI.
    Here you can see and test what it does :)
    
    or completely break it if you really need to...
*/

#include <stdio.h>
#include "../include/salvagui/gui.h"

GUI_window win;

int main(int argc, char * argv[]){
    GUI_initSDL(SDL_INIT_VIDEO);
    GUI_createWindow(&win, "SalvaGUI", 1280, 720, 0);

    GUI_createGUI(&win);
    
    GUI_context * lv = GUI_createLinearView(win.gui);
    GUI_button * btn1 = GUI_getControl(GUI_createButton(lv));
    GUI_button * btn2 = GUI_getControl(GUI_createButton(lv));

    GUI_linearView * lv1 = GUI_getControl(lv);

    lv1->style.backgroundColor = 0x333333;
    lv1->orientation = GUI_ORIENTATION_HORIZONTAL;
    lv1->style.childAlignment.ver = GUI_ALIGNMENT_END;
    lv1->style.childAlignment.hor = GUI_ALIGNMENT_START;
    lv1->rect.w = GUI_SIZE_MATCH_PARENT;

    btn1->style.backgroundColor = 0xFF0000;
    btn1->rect.w = 100;
    btn1->rect.h = 100;

    btn2->style.backgroundColor = 0xFFFF00;
    btn2->rect.w = 100;
    btn2->rect.h = 100;

    GUI_bakeGUI(&win);

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
        
        GUI_renderGUI(&win);
        GUI_updatePixels(&win);
    }

    GUI_destroyWindow(&win);
    SDL_Quit();

    return 0;
}