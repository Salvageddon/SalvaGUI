#pragma once

/*
    A rectangle.
*/
typedef struct{
    int x, y, w, h;
} GUI_rect;

/*
    Also a rectangle, but in float.
*/
typedef struct{
    float x, y, w, h;
} GUI_rectf;

/*
    A rectangle for controls. This means no x and y coordinates.
*/
typedef struct{
    int w, h;
} GUI_rectc;