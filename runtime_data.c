//
// Created by dustin on 05.01.22.
//

#include "runtime_data.h"

//initialisierung eines listelements
void list_element_init(list_element *element) {
    element->next = NULL;
    element->payload = NULL;
    element->typ = NULL;
}
//erstellt ein neues Listelement und initialisiert die daten
list_element* list_element_new() {                              //erstellen eines neuen listelemts allokation des Speichers

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
list_header *list_header_new() {    //erstellen eines neuen list headers
    list_header *new = (list_header *) malloc(sizeof(list_header));
    list_header_init(new);
    return (new);
}
//löscht den inhalt eines listelemts und gibt optional den Speicher von payload frei
void listelement_deleteMembers(list_element *element, _Bool freePayload) {

    if(freePayload){
        free(element->payload);
    }
    element->payload = NULL;
    element->next = NULL;
    element->typ = NULL;
}

//löscht das gesamte listelement und dessesn daten ( evt. deallokieren des Speichers)

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

//allokieren des speichers fürs array
int* init_array(unsigned int row,unsigned int col){
    int* array = (int *) malloc(row*col*sizeof (int ));
    return array;
}

void del_array(int* array){
    free(array);
}

//einfügen von daten an bestimmten punkt (0,0 erste position) //TODO non functional
void insert_data_array(int* array,int* dimY,int dimX,unsigned int row,unsigned int col,int payload){
    *(array + row* (dimX) + col) = payload;
}
//TODO non functional
int* get_array_data(int* array,int* dimY,int dimX,unsigned int row,unsigned int col){
    return (int *) (array + row * (dimX) + col);
}
/*
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