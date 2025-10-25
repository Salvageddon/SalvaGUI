#pragma once

#include "../other/list.h"
#include "gui_rect.h"
#include "gui_events.h"
#include "gui_style.h"

/*
    Stores control, it's child elements and all other necessary
    data for baking, rendering, etc. It's protected.

    To return the control call GUI_getControl().
*/
typedef struct GUI_CONTEXT GUI_context;

/*
    LinearView Control.
    It can store multiple child controls and
    spread them vertically or horizontally.

    Call GUI_createLinearView() to create.
*/
typedef struct{
    GUI_events events; /* All events are stored here. */
    GUI_style style; /* All style data are stored here. */
    GUI_rectc rect; /* Size and position are stored here. */
    int orientation; /* Orientation of the linearView. Vertical or Horizontal*/
} GUI_linearView;

/*
    Button Control.
    It can be clicked. Duh.

    Call GUI_createButton() to create.
*/
typedef struct{
    GUI_events events; /* All events are stored here. */
    GUI_style style; /* All style data are stored here. */
    GUI_rectc rect; /* Size and position are stored here. */
} GUI_button;

/*
    Returns pointer to control stored in the GUI_context.
    If you pass NULL, then it also returns NULL.

    \param context GUI_context storing control.

    \returns A pointer to a control or NULL on error.
*/
void * GUI_getControl(GUI_context * context);

/*
    Do I even have to say it?

    \param parent GUI_context to be parented to the new control.

    \returns GUI_context containing new control.
*/
GUI_context * GUI_createLinearView(GUI_context * parent);

/*
    You know it.

    \param parent GUI_context to be parented to the new control.

    \returns GUI_context containing new control.
*/
GUI_context * GUI_createButton(GUI_context * parent);