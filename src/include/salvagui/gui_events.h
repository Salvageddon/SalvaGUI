#pragma once

/*
    Control event data.
*/
typedef struct{
    int clickStatus; /*If it's clicked. Use GUI_CS_X status enum.*/
    int mouseOverStatus; /*If mouse is over it. Use GUI_MO_X status enum.*/
    int focusStatus; /*If it's focused. Use GUI_FS_X status enum.*/
} GUI_events;

/*
    Control clicked status.
*/
enum GUI_eventClickStatus{
    GUI_CS_NOT_CLICKED,
    GUI_CS_CLICKED
};

/*
    Control has mouse over status.
*/
enum GUI_eventMouseOverStatus{
    GUI_MO_NOT_HOVER,
    GUI_MO_HOVER
};

/*
    Control is being focused on status.
*/
enum GUI_eventFocusStatus{
    GUI_FS_BLURRED,
    GUI_FS_FOCUSED
};