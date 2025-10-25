#pragma once

#include "gui_color.h"

#define GUI_SIZE_MATCH_PARENT -0x100000
#define GUI_SIZE_WRAP_CONTENT -0x200000
#define GUI_ORIENTATION_HORIZONTAL 0
#define GUI_ORIENTATION_VERTICAL 1
#define GUI_ALIGNMENT_START -0x300000
#define GUI_ALIGNMENT_CENTER -0x400000
#define GUI_ALIGNMENT_SPREAD -0x500000
#define GUI_ALIGNMENT_END -0x600000

/*
    Control padding data.
*/
typedef struct{
    int top, right, bottom, left;
} GUI_padding;

/*
    Control margin data.
*/
typedef struct{
    int top, right, bottom, left;
} GUI_margin;

/*
    Aligns child controls vertically and horizontally.
    Here are allowed alignments:

    GUI_ALIGNMENT_START - controls are aligned to the left/top side.
    GUI_ALIGNMENT_CENTER - controls are centered.
    GUI_ALIGNMENT_SPREAD - controls are spread evenly within the parent control.
    GUI_ALIGNMENT_END - controls are aligned to the right/bottom side.
*/
typedef struct{
    int hor, ver;
} GUI_childAlignment;

/*
    Control style data.
*/
typedef struct{
    Uint32 backgroundColor;
    GUI_margin margin;
    GUI_padding padding;
    GUI_childAlignment childAlignment;
} GUI_style;