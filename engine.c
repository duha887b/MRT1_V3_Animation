/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Berechnungs-Modul
 */

#include "engine.h"
#include "runtime_data.h"

//TODO get pixel of matrix --> add around pixels --> check

void cal_nextAnimaionStep(list_header* list){


   int *current_array = get_array(list);       //tn
   int *next_array = new_array(list);          //tn + 1


   int cols = get_X(list) + 2;                 //dimensionen des arrays
   int rows = get_Y(list) + 2;

   printf("X:%d,Y:%d", get_X(list), get_Y(list));





    //if randpixel

    //else







   // set_array(list,next_array);

}

