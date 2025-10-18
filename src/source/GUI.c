#include "../include/salvagui/gui.h"

#include <stdio.h>

typedef struct GUI_BASE{
    GUI_window * parent;
} GUI_base;

typedef struct GUI_CONTEXT{
    void * control;
    int type, indexSelf;
    GUI_rect * rect;
    GUI_events * events;
    GUI_style * style;
    GUI_base * base;
    list childControls;
    SDL_Surface * render;
} GUI_context;

enum GUI_controlTypes{
    GUI_CTR_TYPE_BASE,
    GUI_CTR_TYPE_LINEARVIEW,
    GUI_CTR_TYPE_BUTTON
};

//gui.h


int GUI_initSDL(Uint32 flags){
    int initerr = SDL_Init(flags);

    if(!initerr){
        printf("SalvaGUI (initSDL()): Failure during SDL initialization\n");
        return 1;
    }

    return 0;
}


//gui_color.h


colorRGB GUI_getColorRGB(Uint32 color, SDL_PixelFormat format){
    colorRGB col;

    SDL_GetRGB(color, 
        SDL_GetPixelFormatDetails(format),
        NULL,
        &col.r, &col.g, &col.b);

    return col;
}

colorRGBA GUI_getColorRGBA(Uint32 color, SDL_PixelFormat format){
    colorRGBA col;

    SDL_GetRGBA(color, 
        SDL_GetPixelFormatDetails(format),
        NULL,
        &col.r, &col.g, &col.b, &col.a);

    return col;
}

Uint32 GUI_mapColorRGB(colorRGB color, SDL_PixelFormat format){
    return SDL_MapRGB(SDL_GetPixelFormatDetails(format),
        NULL,
        color.r, color.g, color.b);
}

Uint32 GUI_mapColorRGBA(colorRGBA color, SDL_PixelFormat format){
    return SDL_MapRGBA(SDL_GetPixelFormatDetails(format),
        NULL,
        color.r, color.g, color.b, color.a);
}


//gui_render.h


void GUI_setPixel(GUI_window * win, int x, int y, Uint32 color){
    GUI_setPixelOnSur(win->sur, x, y, color);
}

void GUI_setPixelOnSur(SDL_Surface * sur, int x, int y, Uint32 color){
    Uint32 * pixels = sur->pixels;
    pixels[y * sur->w + x] = color;
}

Uint32 GUI_getPixel(GUI_window * win, int x, int y){
    return GUI_getPixelFromSur(win->sur, x, y);
}

Uint32 GUI_getPixelFromSur(SDL_Surface * sur, int x, int y){
    Uint32 * pixels = sur->pixels;
    return pixels[y * sur->w + x];
}

void GUI_updatePixels(GUI_window * win){
    SDL_UpdateWindowSurface(win->win);
}

void bakeControl(GUI_context * context){
    SDL_DestroySurface(context->render);

    int w = context->rect->w;
    int h = context->rect->h;

    SDL_PixelFormat format = context->base->parent->sur->format;

    context->render = SDL_CreateSurface(w, h, format);

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            GUI_setPixelOnSur(context->render, x, y, context->style->backgroundColor);
        }
    }
}

void bakeLoopControlList(list * l){
    for(int i = 0; i < l->length; i++){
        GUI_context * context = LST_getValue(*l, i);
        bakeControl(context);
        bakeLoopControlList(&context->childControls);
    }
}

void GUI_bakeControls(GUI_window * win){
    if(win == NULL){
        printf("SalvaGUI (bakeControlsFromWindow()): Window must not be NULL\n");
        return;
    }

    if(win->gui == NULL){
        printf("SalvaGUI (bakeControlsFromWindow()): Base context must not be NULL\n");
        return;
    }

    bakeLoopControlList(&win->gui->childControls);
}

void renderControl(GUI_context * context, GUI_window * win){
    int w = context->rect->w;
    int h = context->rect->h;

    int x1 = context->rect->x;
    int y1 = context->rect->y;

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            GUI_setPixel(win, x1 + x, y1 + y, context->style->backgroundColor);
        }
    }
}

void renderLoopControlList(list * l, GUI_window * win){
    for(int i = 0; i < l->length; i++){
        GUI_context * context = LST_getValue(*l, i);
        renderControl(context, win);
        renderLoopControlList(&context->childControls, win);
    }
}

void GUI_renderControls(GUI_window * win){
    if(win == NULL){
        printf("SalvaGUI (bakeControlsFromWindow()): Window must not be NULL\n");
        return;
    }

    if(win->gui == NULL){
        printf("SalvaGUI (bakeControlsFromWindow()): Base context must not be NULL\n");
        return;
    }

    renderLoopControlList(&win->gui->childControls, win);
}

void GUI_refreshScreen(GUI_window * win){
    for(int y = 0; y < win->h; y++){
        for(int x = 0; x < win->w; x++){
            GUI_setPixel(win, x, y, 0);
        }
    }
}


//gui_controls.h


GUI_context * createContext(void * control, GUI_events * events, GUI_style * style, GUI_rect * rect, GUI_base * base, int type){
    GUI_context * o = malloc(sizeof(GUI_context));

    o->control = control;
    o->type = type;
    o->rect = rect;
    o->events = events;
    o->style = style;
    o->base = base;
    o->childControls = LST_createList();
    o->render = NULL;
    o->indexSelf = 0;

    return o;
}

void destroyContext(GUI_context * anihilateme){
    free(anihilateme->control);
    SDL_DestroySurface(anihilateme->render);
    free(anihilateme);
}

void destroyContextLoop(list * l){
    for(int i = 0; i < l->length; i++){
        GUI_context * context = LST_getValue(*l, i);
        destroyContextLoop(&context->childControls);
        LST_clearList(&context->childControls, 1);
        destroyContext(context);
    }
}

GUI_events initEvents(void){
    return (GUI_events){
        GUI_CS_NOT_CLICKED,
        GUI_MO_NOT_HOVER,
        GUI_FS_BLURRED
    };
}

GUI_style initStyle(void){
    return (GUI_style){
        0
    };
}

GUI_rect initRect(void){
    return (GUI_rect){
        0, 0, 0, 0
    };
}

void calculateControlPos(GUI_context * parent, GUI_context * context){
    if(parent->childControls.length < 1){
        return;
    }

    GUI_context * last = LST_getValue(parent->childControls, parent->childControls.length);

    context->rect->x = last->rect->x + last->rect->w;
    context->rect->y = last->rect->y + last->rect->h;
}

GUI_linearView * GUI_createLinearView(GUI_context * parent, GUI_context * linearView){
    if(parent == NULL){
        printf("SalvaGUI (createLinearView()): Parent context must not be NULL\n");
        return NULL;
    }

    GUI_linearView * _linearView = malloc(sizeof(GUI_linearView));

    _linearView->events = initEvents();
    _linearView->style = initStyle();
    _linearView->rect = initRect();
    
    _linearView->orientation = GUI_ORIENTATION_HORIZONTAL;

    GUI_context * context = createContext(_linearView, 
        &_linearView->events, 
        &_linearView->style, 
        &_linearView->rect,
        parent->base, 
        GUI_CTR_TYPE_LINEARVIEW);

    if(linearView != NULL){
        destroyContext(linearView);
        linearView = context;
    }

    calculateControlPos(parent, context);
    LST_addElement(&parent->childControls, context);

    context->indexSelf = parent->childControls.length - 1;

    return _linearView;
}

GUI_button * GUI_createButton(GUI_context * parent, GUI_context * button){
    if(parent == NULL){
        printf("SalvaGUI (createButton()): Parent context must not be NULL\n");
        return NULL;
    }

    GUI_button * _button = malloc(sizeof(GUI_button));

    _button->events = initEvents();
    _button->style = initStyle();
    _button->rect = initRect();
    
    _button->text = "";

    GUI_context * context = createContext(_button, 
        &_button->events, 
        &_button->style, 
        &_button->rect, 
        parent->base,
        GUI_CTR_TYPE_BUTTON);

    if(button != NULL){
        destroyContext(button);
        button = context;
    }

    calculateControlPos(parent, context);
    context->indexSelf = parent->childControls.length;

    LST_addElement(&parent->childControls, context);

    return _button;
}


//gui_window.h


int GUI_createWindow(GUI_window * win, char * title, int w, int h, Uint32 flags){
    win->win = SDL_CreateWindow(title, w, h, flags);

    if(!win->win){
        printf("SalvaGUI (createWindow()): Failure during window creation\n");
        return 1;
    }

    win->sur = SDL_GetWindowSurface(win->win);

    win->w = w;
    win->h = h;

    return 0;
}

void GUI_destroyWindow(GUI_window * win){
    GUI_destroyGUI(win);

    SDL_DestroyWindowSurface(win->win);
    SDL_DestroyWindow(win->win);
}

int GUI_createGUI(GUI_window * win){
    if(win == NULL){
        printf("SalvaGUI (createGUI()): Window must not be NULL\n");
        return 1;
    }
    
    GUI_base * base = malloc(sizeof(GUI_base));

    base->parent = win;

    if(win->gui != NULL){
        GUI_destroyGUI(win);
    }
    
    win->gui = createContext(base, NULL, NULL, NULL, base, GUI_CTR_TYPE_BASE);

    return 0;
}

void GUI_destroyGUI(GUI_window * win){
    if(win->gui == NULL){
        printf("SalvaGUI (destroyGUI()): This window does not have GUI");
        return;
    }

    destroyContextLoop(&win->gui->childControls);
    destroyContext(win->gui);
}