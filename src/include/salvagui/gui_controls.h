#pragma once

#include "../other/list.h"
#include "gui_rect.h"
#include "gui_events.h"
#include "gui_style.h"

#define GUI_SIZE_MATCH_PARENT -0x100000
#define GUI_SIZE_WRAP_CONTENT -0x200000
#define GUI_ORIENTATION_HORIZONTAL 0
#define GUI_ORIENTATION_VERTICAL 1
#define GUI_POSITION_START -0x300000
#define GUI_POSITION_CENTER -0x400000
#define GUI_POSITION_SPREAD -0x500000
#define GUI_POSITION_END -0x600000

typedef struct GUI_CONTEXT GUI_context;

typedef struct{
    GUI_events events;
    GUI_style style;
    GUI_rectc rect;
    int orientation;
} GUI_linearView;

typedef struct{
    GUI_events events;
    GUI_style style;
    GUI_rectc rect;
} GUI_button;

void * GUI_getControl(GUI_context * context);
GUI_context * GUI_createLinearView(GUI_context * parent);
GUI_context * GUI_createButton(GUI_context * parent);