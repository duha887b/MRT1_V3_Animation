//
// Created by dustin on 05.01.22.
//

#ifndef MRT1_V3_ANIMATION_RUNTIME_DATA_H
#define MRT1_V3_ANIMATION_RUNTIME_DATA_H

#include <stdlib.h>
#include <stdio.h>


// List element typen für auswertung des Pointers
/*
 * 0 X --> Spalten (int)
 * 1 Y --> Zeilen (int)
 * 2 AN_COUNTER --> derzeitiger Animationsschritt (int)
 * 3 AN_MAX --> maximale Anzahl an Animationsschritten (int)
 * 4 DELAY --> Pause zwischen Animationsschritten in ms (long)
 * 5 ARRAY --> Liste die das Array des Animationspuffers beinhaltet (list)
 * 6 VOID --> Zusatzinformationen (void)
 */
typedef enum {
    X,Y,AN_COUNTER,AN_MAX,DELAY,ARRAY,VOID
}typ;



//Inhalt eines List elements
typedef struct list_el_t{
    struct list_el_t *next;
    void *payload;
    typ *typ;
}list_element;

//struktur List header
typedef struct list_t{
    list_element *head;
    list_element *tail;
}list_header;

//Schnittstelle

//erstellen einer Liste mit den Elemnten (X,Y,AN_COUNTER,AN_MAX,DELAY,ARRAY)
list_header* new_specific_list();

// anderes Element des typs void der Liste hinzufügen
//void add_listElement(list_element* le);



//getter setter X-Achse
int get_X(list_header* list);
void set_X(list_header* list, int* x);

//getter setter Y-Achse
int get_Y(list_header* list);
void set_Y(list_header* list, int* y);

//getter setter Animationszähler
int get_animation_counter(list_header* list);
void set_animation_counter(list_header* list, int* counter);

//getter setter maximale Animationsschritte
int get_animation_maxC(list_header* list);
void set_animation_maxC(list_header* list, int* maxC);

//getter setter Pause zwischen Animationsschritten
long get_delay(list_header* list);
void set_delay(list_header* list, long* delay);

//getter setter array-pointer
int* get_array(list_header* list);
void set_array(list_header* list, int* array);


#endif //MRT1_V3_ANIMATION_RUNTIME_DATA_H
