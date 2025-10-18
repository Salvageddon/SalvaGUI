#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement listElement;

typedef struct{
    listElement * origin;
    int length;
} list;

list LST_createList(void);
void LST_addElement(list * l, void * val);
void LST_removeElement(list * l, int index, int freeval);
void * LST_getValue(list l, int index);
void LST_setValue(list * l, int index, void * val);
int LST_findByPointer(list l, void * pointer);
void LST_addElementAt(list * l, int index, void * wart);
void LST_clearList(list * l, int freeval);