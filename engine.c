/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Berechnungs-Modul
 */

#include "engine.h"
#include "runtime_data.h"
#include <string.h>




void cal_nextAnimaionStep(list_header* list){

    int *current_array = get_array(list);       //tn
    int *next_array = new_array(list);          //tn + 1

    int cols = get_X(list) + 2;                 //dimensionen des arrays
    int rows = get_Y(list) + 2;

    int* counter = get_animation_counter(list); //pointer des Animationscounters holen



//temp code
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", current_array[i * cols + j]);
        printf("\n");
    }
//



   for(int r = 0;r<rows;r++){
       for(int c = 0; c<cols ;c++){
           //r,c iter über alle Elemente der matrix r,c
            //temporärer zähler der belegten Nachbarn

           //iterieren über die nachbarn des pixels m,n
           int tmp_count = 0;
           for(int m = r-1; m<=r+1 ;m++ ){
               for(int n = c-1; n<=c+1 ;n++){

                   if((n==c && m==r)){
                       continue;
                   }else if(n<0 || m<0){
                       continue;
                   }else if(n>cols || m>rows){
                       continue;
                   }

                   tmp_count = tmp_count + (current_array[m*cols+n]);
               }
           }


           // set new pixel in next_array

           if(current_array[r*cols+c] == 0 && tmp_count == 3){
               next_array[r*cols+c] = 1;
               continue;
           }else if(current_array[r*cols+c] == 1 && (tmp_count == 3||tmp_count == 2)) {
               next_array[r * cols + c] = 1;
               continue;
           }else if(current_array[r*cols+c] == 1 && tmp_count < 2) {
               next_array[r * cols + c] = 0;
               continue;
           }else if(current_array[r*cols+c] == 1 && tmp_count > 3) {
               next_array[r * cols + c] = 0;
               continue;
           }

       }
   }
/*
   printf("_____________________\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", next_array[i * cols + j]);
        printf("\n");
    }
*/
    *counter = *counter+1;
    memcpy(current_array, next_array, (get_X(list)+2)*(get_Y(list)+2)*sizeof (int ));

    free(next_array);

// temp
    printf("_____________________\n");


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", current_array[i * cols + j]);
        printf("\n");
    }
        printf("counter:%d",*counter);

}




