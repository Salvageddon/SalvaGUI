#pragma once

#include "../other/list.h"
#include "gui_rect.h"
#include "gui_events.h"
#include "gui_style.h"

#define GUI_SIZE_MATCH_PARENT -0x100000
#define GUI_SIZE_WRAP_CONTENT -0x200000
#define GUI_ORIENTATION_HORIZONTAL 0
#define GUI_ORIENTATION_VERTICAL 1

typedef struct GUI_CONTEXT GUI_context;

typedef struct{
    GUI_events events;
    GUI_style style;
    GUI_rect rect;
    int orientation;
} GUI_linearView;

typedef struct{
    GUI_events events;
    GUI_style style;
    GUI_rect rect;
    char * text; //DO NOT ALLOCATE DYNAMICALLY!!!
} GUI_button;

GUI_linearView * GUI_createLinearView(GUI_context * parent, GUI_context * linearView);
GUI_button * GUI_createButton(GUI_context * parent, GUI_context * button);