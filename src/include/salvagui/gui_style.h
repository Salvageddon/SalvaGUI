#pragma once

#include "gui_color.h"

typedef struct{
    int top, right, bottom, left;
} GUI_margin, GUI_padding;

typedef struct{
    int hor, ver;
} GUI_childAlignment;

typedef struct{
    Uint32 backgroundColor;
    GUI_margin margin;
    GUI_padding padding;
    GUI_childAlignment childAlignment;
} GUI_style;