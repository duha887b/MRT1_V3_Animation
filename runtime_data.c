//
// Created by dustin on 05.01.22.
//

#include "runtime_data.h"

//initialisierung eines list-elements
void list_element_init(list_element *element) {
    element->next = NULL;
    element->payload = NULL;
    element->typ = NULL;
}
//erstellt ein neues Listelement und initialisiert die daten
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
list_header* list_header_new() {    //erstellen eines neuen list headers
    list_header *new = (list_header *) malloc(sizeof(list_header));
    list_header_init(new);
    return (new);
}
/*
//löscht den inhalt eines listelemts und gibt optional den Speicher von payload frei
void listelement_deleteMembers(list_element *element, _Bool freePayload) {

    if(freePayload){
        free(element->payload);
    }
    element->payload = NULL;
    element->next = NULL;
    element->typ = NULL;
}
*/
//löscht das gesamte listelement und dessen daten ( evt. deallokieren des Speichers)
/*
void listelement_delete(list_header *header, list_element *element, _Bool freePayload) {

    list_element *tmp;
    list_element *del;

    tmp = header->head;

    if (tmp == element) {            //delete head element

        if(tmp->next == NULL){      // if head element is the last element
            header->tail = NULL;
            header->head = NULL;
            goto next;
        }

        header->head = (list_element *) tmp->next;
        goto next;
    }

    while (tmp->next != NULL) {
        if (tmp->next == element) {

            del = (list_element *) tmp->next;
            tmp->next = del->next;

            if (tmp->next == NULL) {
                header->tail = tmp;
            }

            goto next;
        }
        tmp = tmp->next;
    }

    next:
    listelement_deleteMembers(element,freePayload);         // clear or delete members of list_element
    if(freePayload){
        free(element);                                      //deallocate element himself
        element = NULL;
    }
}
*/
// fügt das listelement einer Liste hinzu und dem listelement seine Daten
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
//gesamter inhalt der Liste wird vom header gelöst (z.B zum neubefüllen der List)
void list_clear(list_header *header) {
    header->head = NULL;
    header->tail = NULL;
}

list_header* new_specific_list(){

    // Achtung wegen Verfügbarkeit ??
    typ typ_col = X;
    typ typ_row = Y;
    typ typ_an_counter = AN_COUNTER;
    typ typ_an_max = AN_MAX;
    typ typ_delay =DELAY;
    typ typ_array = ARRAY;

    // erzeugen eines neuen Listenkopfes
    list_header* RuntimeData = list_header_new();

    //erzeugen neuer elemente
    list_element* x = list_element_new();
    list_element* y = list_element_new();
    list_element* counter = list_element_new();
    list_element* max_count = list_element_new();
    list_element* delay = list_element_new();
    list_element* array = list_element_new();

    //anfügen der elemente an die Liste ohne Payload
    listelement_append(RuntimeData,x,NULL,&typ_col);
    listelement_append(RuntimeData,y,NULL,&typ_row);
    listelement_append(RuntimeData,counter,NULL,&typ_an_counter);
    listelement_append(RuntimeData,max_count,NULL,&typ_an_max);
    listelement_append(RuntimeData,delay,NULL,&typ_delay);
    listelement_append(RuntimeData,array,NULL,&typ_array);

    // zurückgeben des Listenkopfes
    return RuntimeData;

}

// filtern nach gesuchtem Datenpunkt
list_element* search_data(list_header* header, typ t){
    list_element *tmp;
    tmp = header->head;

    if(header->head == NULL && header->tail == NULL){
        fprintf(stderr," bad list (no data found) !!!! ");
        return NULL;
    }

    while (tmp != NULL){
        if(*(tmp->typ) == t) {
            return tmp;
        }

        tmp = tmp->next;
    }


    return NULL;

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

int get_animation_counter(list_header* list){
    list_element *tmp = search_data(list,AN_COUNTER);
    return *((int*) tmp->payload);
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

// suchen des Datenpunktes und ersetzten des pointers payload auf eine neue Adresse
void set_data(list_header *header, typ t,void* payload){
    list_element *tmp = header->head;

    if(header->head == NULL && header->tail == NULL){
        fprintf(stderr," bad list (no element to set !!!!) ");
        return ;
    }

    while (tmp != NULL){
        if(*(tmp->typ) == t) {
            tmp->payload = payload;
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


int* new_array(list_header* list){
    int* array = (int *)malloc((get_X(list)+2)*(get_Y(list)+2)*sizeof (int ));
    return array;
}









/*
//allokieren des speichers fürs array
int* init_array(unsigned int row,unsigned int col){
    int* array = (int *) malloc(row*col*sizeof (int ));
    return array;
}

void del_array(int* array){
    free(array);
}

//einfügen von daten an bestimmten punkt (0,0 erste position)
void insert_data_array(int* array,int* dimY,int dimX,unsigned int row,unsigned int col,int payload){
    *(array + row* (dimX) + col) = payload;
}

int* get_array_data(int* array,int* dimY,int dimX,unsigned int row,unsigned int col){
    return (int *) (array + row * (dimX) + col);
}

int main(){
    int *arr = init_array(2,2);
    insert_data_array(arr,0,0,23);
    insert_data_array(arr,0,1,7);
    insert_data_array(arr,1,0,13);
    insert_data_array(arr,1,1,9);

    printf("\n%d", *(get_array_data(arr,0,0)));

    return 0;
}
*/