#pragma once

typedef struct{
    int clickStatus;
    int mouseOverStatus;
    int focusStatus;
} GUI_events;

enum GUI_eventClickStatus{
    GUI_CS_NOT_CLICKED,
    GUI_CS_CLICKED
};

enum GUI_eventMouseOverStatus{
    GUI_MO_NOT_HOVER,
    GUI_MO_HOVER
};

enum GUI_clickStatus{
    GUI_FS_BLURRED,
    GUI_FS_FOCUSED
};