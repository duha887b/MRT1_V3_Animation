//
// Created by dustin on 05.01.22.
//

#include "runtime_data.h"

//Initialisierung eines list-elements
void list_element_init(list_element *element) {
    element->next = NULL;
    element->payload = NULL;
    element->typ = NULL;
}
//erstellt ein neues list-elements und initialisiert die Daten
list_element* list_element_new() {

    list_element *new = (list_element *) malloc(sizeof(list_element));
    list_element_init(new);
    return (new);
}
//Initialisieren eines Listenkopfes
void list_header_init(list_header *header) {
    header->head = NULL;
    header->tail = NULL;

}

// erstellt einen neuen Listenkopf (Liste)
list_header* list_header_new() {
    list_header *new = (list_header *) malloc(sizeof(list_header));
    list_header_init(new);
    return (new);
}

// fügt das list-element einer Liste hinzu und dem list-element seine Daten
void listelement_append(list_header *l, list_element *le, void *payload, typ *typ) {

    // no elements
    le->payload = payload;
    le->next = NULL;
    le->typ = typ;

    if (l->head == NULL && l->tail == NULL){
        l->head = le;
        l->tail = le;
        return;
    }

    // 1 element
    if (l->head == l->tail) {
        l->head->next = le;
        l->tail = le;
        return;
    }

    l->tail->next =  le;
    l->tail = le;

}
//gesamter Inhalt der Liste wird vom header gelöst (z.B. zum neubefüllen der List)
void list_clear(list_header *header) {
    header->head = NULL;
    header->tail = NULL;
}

// erstellt die eine Liste mit den der Aufgabe entsprechenden Elementen
list_header* new_specific_list(){

    // speicher für Datentyp der list-elemente allokieren
    typ* typ_col = (typ*) malloc(sizeof (typ));
    *typ_col = X;
    typ *typ_row = (typ*) malloc(sizeof (typ));
    *typ_row = Y;
    typ *typ_an_counter = (typ*) malloc(sizeof (typ));
    *typ_an_counter = AN_COUNTER;
    typ *typ_an_max = (typ*) malloc(sizeof (typ));
    *typ_an_max = AN_MAX;
    typ *typ_delay =(typ*) malloc(sizeof (typ));
    *typ_delay = DELAY;
    typ *typ_array = (typ*) malloc(sizeof (typ));
    *typ_array = ARRAY;



    // erzeugen eines neuen Listenkopfes
    list_header* RuntimeData = list_header_new();

    //erzeugen neuer Elemente
    list_element* x = list_element_new();
    list_element* y = list_element_new();
    list_element* counter = list_element_new();
    list_element* max_count = list_element_new();
    list_element* delay = list_element_new();
    list_element* array = list_element_new();

    //anfügen der Elemente an die Liste ohne Payload
    listelement_append(RuntimeData,x,NULL,typ_col);
    listelement_append(RuntimeData,y,NULL,typ_row);
    listelement_append(RuntimeData,counter,NULL,typ_an_counter);
    listelement_append(RuntimeData,max_count,NULL,typ_an_max);
    listelement_append(RuntimeData,delay,NULL,typ_delay);
    listelement_append(RuntimeData,array,NULL,typ_array);

    // zurückgeben des Listenkopfes
    return RuntimeData;

}

// filtern nach gesuchtem Datenpunkt
list_element* search_data(list_header* header, typ t){
    list_element *tmp;
    tmp = header->head;

    // Abbruch, wenn die Liste leer ist
    if(header->head == NULL && header->tail == NULL){
        fprintf(stderr," bad list (no data found) !!!! ");
        return NULL;
    }

    // iterieren über die Liste bis des Elements des gewünschten Typs gefunden wird
    while (tmp != NULL){
        if(*(tmp->typ) == t) {
            return tmp;     // gibt das passende Element des gesuchten typs zurück
        }

        tmp = tmp->next;
    }


    return NULL; // wenn kein entsprechendes Element gefunden wurde

}

// getter  func.
int get_X(list_header* list){
    list_element *tmp = search_data(list,X);
    return *((int*) tmp->payload);
}

int get_Y(list_header* list){
    list_element *tmp = search_data(list,Y);
    return *((int*) tmp->payload);
}

int* get_animation_counter(list_header* list){
    list_element *tmp = search_data(list,AN_COUNTER);
    return ((int*) tmp->payload);
}

int get_animation_maxC(list_header* list){
    list_element *tmp = search_data(list,AN_MAX);
    return *((int*) tmp->payload);
}

long get_delay(list_header* list){
    list_element *tmp = search_data(list,DELAY);
    return *((long*) tmp->payload);
}

int* get_array(list_header* list){
    list_element *tmp = search_data(list,ARRAY);
    return ((int*) tmp->payload);
}

// suchen des Datenpunktes und ersetzten des Pointers payload auf eine neue Adresse
void set_data(list_header *header, typ t,void* payload){
    list_element *tmp = header->head;

    if(header->head == NULL && header->tail == NULL){
        fprintf(stderr," bad list (no element to set !!!!) ");
        return ;
    }

    while (tmp != NULL){  //iterieren bis Element gefunden
        if(*(tmp->typ) == t) {
            tmp->payload = payload; //setzten des neuen Pointers
            return ;
        }

        tmp = tmp->next;
    }
    return;


}
//setter func.
void set_X(list_header* list, int* x){
    set_data(list,X,x);
    return;
}

void set_Y(list_header* list, int* y){
    set_data(list,Y,y);
    return;
}

void set_animation_counter(list_header* list, int* counter){
    set_data(list,AN_COUNTER,counter);
    return;
}

void set_animation_maxC(list_header* list, int* maxC){
    set_data(list,AN_MAX,maxC);
    return;
}

void set_delay(list_header* list, long* delay){
    set_data(list,DELAY,delay);
    return;
}

void set_array(list_header* list, int* array){
    set_data(list,ARRAY,array);
    return;
}

// allokiert im Speicher einen bereich welcher ein Array in der geforderten Größe fassen kann
int* new_array(list_header* list){
    int* array = (int *)malloc((get_X(list)+2)*(get_Y(list)+2)*sizeof (int ));
    return array;
}
void free_all(list_header* list){
    free(search_data(list,ARRAY));
}



