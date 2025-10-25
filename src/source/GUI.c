#include "../include/salvagui/gui.h"

#include <stdio.h>

typedef struct GUI_BASE{
    GUI_window * parent;
    GUI_rectc rect;
    GUI_style style;
} GUI_base;

typedef struct{
    int onlyOneChild, * orientation;
} GUI_viewHandler;

typedef struct GUI_CONTEXT{
    void * control;
    int type, indexSelf, x, y;
    struct GUI_CONTEXT * parent;
    GUI_events * events;
    GUI_style * style;
    GUI_rectc * rect;
    GUI_base * base;
    list childControls;
    SDL_Surface * render;
    GUI_viewHandler viewHandler;
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

void calculateSize(GUI_context * context){
    int verw = 0, verh = 0, horw = 0, horh = 0;

    for(int i = 0; i < context->childControls.length; i++){
        GUI_context * child = LST_getValue(context->childControls, i);

        verh += child->rect->h;  
        verw = verw < child->rect->w ? child->rect->w : verw;

        horw += child->rect->w;
        horh = horh < child->rect->h ? child->rect->h : horh;

        calculateSize(child);
    }

    switch(context->rect->w){
        case GUI_SIZE_WRAP_CONTENT:
            context->rect->w = horw;
        break;

        case GUI_SIZE_MATCH_PARENT:
            context->rect->w = context->parent->rect->w;
        break;

        default:
            if(context->rect->w < verw){
                context->rect->w = verw;
            }
        break;
    }

    switch(context->rect->h){
        case GUI_SIZE_WRAP_CONTENT:
            context->rect->h = horh;
        break;

        case GUI_SIZE_MATCH_PARENT:
            context->rect->h = context->parent->rect->h;
        break;

        default:
            if(context->rect->h < horh){
                context->rect->h = horh;
            }
        break;
    }
}

void calculatePos(GUI_context * context){
    int childX = 0;
    int childY = 0;

    childX += context->x;
    childY += context->y;

    for(int i = 0; i < context->childControls.length; i++){
        GUI_context * child = LST_getValue(context->childControls, i);

        switch(context->style->childAlignment.hor){
            case GUI_POSITION_CENTER:
            break;

            case GUI_POSITION_SPREAD:
            break;

            case GUI_POSITION_END:
                child->x = context->rect->w - childX - child->rect->w;
                if(context->viewHandler.orientation){
                    int orientation = *context->viewHandler.orientation;
                    if(orientation == GUI_ORIENTATION_HORIZONTAL){
                        childX += child->rect->w;
                    }
                }
            break;

            default:
                child->x = childX;
                if(context->viewHandler.orientation){
                    int orientation = *context->viewHandler.orientation;
                    if(orientation == GUI_ORIENTATION_HORIZONTAL){
                        childX += child->rect->w;
                    }
                }
            break;
        }

        switch(context->style->childAlignment.ver){
            case GUI_POSITION_CENTER:
            break;

            case GUI_POSITION_SPREAD:
            break;

            case GUI_POSITION_END:
                child->y = context->rect->h - childY - child->rect->h;
                if(context->viewHandler.orientation){
                    int orientation = *context->viewHandler.orientation;
                    if(orientation == GUI_ORIENTATION_VERTICAL){
                        childY += child->rect->h;
                    }
                }
            break;

            default:
                child->y = childY;
                if(context->viewHandler.orientation){
                    int orientation = *context->viewHandler.orientation;
                    if(orientation == GUI_ORIENTATION_VERTICAL){
                        childY += child->rect->h;
                    }
                }
            break;
        }

        calculatePos(child);
    }
}

void bakeControl(GUI_context * context){
    for(int i = 0; i < context->childControls.length; i++){
        GUI_context * child = LST_getValue(context->childControls, i);
        bakeControl(child);
        
        SDL_DestroySurface(child->render);

        int w = child->rect->w;
        int h = child->rect->h;

        SDL_PixelFormat format = child->base->parent->sur->format;

        child->render = SDL_CreateSurface(w, h, format);

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                GUI_setPixelOnSur(child->render, x, y, child->style->backgroundColor);
            }
        }
    }
}

void GUI_bakeGUI(GUI_window * win){
    if(win == NULL){
        printf("SalvaGUI (bakeGUI()): Window must not be NULL\n");
        return;
    }

    if(win->gui == NULL){
        printf("SalvaGUI (bakeGUI()): Base context doesn't exist\n");
        return;
    }

    calculateSize(win->gui);
    calculatePos(win->gui);
    bakeControl(win->gui);
}

void renderControl(GUI_context * context, GUI_window * win){
    if(context->type != GUI_CTR_TYPE_BASE && context->type){
        int w = context->render->w;
        int h = context->render->h;

        int x1 = context->x;
        int y1 = context->y;

        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                GUI_setPixel(win, x1 + x, y1 + y, GUI_getPixelFromSur(context->render, x, y));
            }
        }
    }

    for(int i = 0; i < context->childControls.length; i++){
        GUI_context * child = LST_getValue(context->childControls, i);
        renderControl(child, win);
    }
}

void GUI_renderGUI(GUI_window * win){
    if(win == NULL){
        printf("SalvaGUI (renderGUI()): Window must not be NULL\n");
        return;
    }

    if(win->gui == NULL){
        printf("SalvaGUI (renderGUI()): Base context doesn't exist\n");
        return;
    }

    renderControl(win->gui, win);
}

void GUI_refreshScreen(GUI_window * win){
    for(int y = 0; y < win->h; y++){
        for(int x = 0; x < win->w; x++){
            GUI_setPixel(win, x, y, 0);
        }
    }
}


//gui_controls.h


GUI_context * createContext(void * control, GUI_context * parent, GUI_viewHandler viewHandler, GUI_events * events, GUI_style * style, GUI_rectc * rect, GUI_base * base, int type){
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
    o->viewHandler = viewHandler;
    o->parent = parent;

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
        0x000000,
        (GUI_margin){10, 10, 10, 10},
        (GUI_padding){10, 10, 10, 10}
    };
}

GUI_rectc initRect(void){
    return (GUI_rectc){
        GUI_SIZE_WRAP_CONTENT,
        GUI_SIZE_WRAP_CONTENT
    };
}

void * GUI_getControl(GUI_context * context){
    if(context->type != GUI_CTR_TYPE_BASE) return context->control;
}

GUI_context * GUI_createLinearView(GUI_context * parent){
    if(parent == NULL){
        printf("SalvaGUI (createLinearView()): Parent context must not be NULL\n");
        return NULL;
    }

    GUI_linearView * linearView = malloc(sizeof(GUI_linearView));

    linearView->events = initEvents();
    linearView->style = initStyle();
    linearView->rect = initRect();
    
    linearView->orientation = GUI_ORIENTATION_HORIZONTAL;

    GUI_context * context = createContext(linearView, 
        parent,
        (GUI_viewHandler){0, &linearView->orientation},
        &linearView->events, 
        &linearView->style, 
        &linearView->rect,
        parent->base, 
        GUI_CTR_TYPE_LINEARVIEW);

    LST_addElement(&parent->childControls, context);

    context->indexSelf = parent->childControls.length - 1;

    return context;
}

GUI_context * GUI_createButton(GUI_context * parent){
    if(parent == NULL){
        printf("SalvaGUI (createButton()): Parent context must not be NULL\n");
        return NULL;
    }

    GUI_button * button = malloc(sizeof(GUI_button));

    button->events = initEvents();
    button->style = initStyle();
    button->rect = initRect();

    GUI_context * context = createContext(button, 
        parent,
        (GUI_viewHandler){1, 0},
        &button->events, 
        &button->style, 
        &button->rect, 
        parent->base,
        GUI_CTR_TYPE_BUTTON);

    context->indexSelf = parent->childControls.length;

    LST_addElement(&parent->childControls, context);

    return context;
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

    base->style = initStyle();
    
    base->parent = win;
    base->rect = (GUI_rectc){win->w, win->h};
    base->style.margin = (GUI_margin){0, 0, 0, 0};
    base->style.padding = (GUI_padding){0, 0, 0, 0};

    if(win->gui != NULL){
        GUI_destroyGUI(win);
    }
    
    win->gui = createContext(base, NULL, (GUI_viewHandler){1, 0}, NULL, &base->style, &base->rect, base, GUI_CTR_TYPE_BASE);

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