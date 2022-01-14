/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Berechnungs-Modul
 */

#include "engine.h"
#include "runtime_data.h"

// für memcpy
#include <string.h>




void cal_nextAnimaionStep(list_header* list){

    int *current_array = get_array(list);       //tn
    int *next_array = new_array(list);          //tn + 1

    int cols = get_X(list) + 2;                 //dimensionen des arrays
    int rows = get_Y(list) + 2;

    int* counter = get_animation_counter(list); //pointer des Animationszählers holen



//temp code
/*
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", current_array[i * cols + j]);
        printf("\n");
    }
//
*/


   for(int r = 0;r<rows;r++){                   // iteriert über die Zeilen des Arrays
       for(int c = 0; c<cols ;c++){             // iteriert über die Spalten des Arrays

           int tmp_count = 0;                   // temporärer Zähler der belegten Nachbarn eines Pixels
           for(int m = r-1; m<=r+1 ;m++ ){      // iteriert über die Zeilen der Nachbarn
               for(int n = c-1; n<=c+1 ;n++){   // iteriert über die Spalten der Nachbarn

                   if((n==c && m==r)){          //überspringen des mittleren Pixels
                       continue;
                   }else if(n<0 || m<0){        //überspringen eines Pixels welches links außerhalb des bereiches liegt
                       continue;
                   }else if(n>cols || m>rows){  //überspringen eines Pixels welches rechts außerhalb des bereiches liegt
                       continue;
                   }

                   if(current_array[m*cols+n] !=1 && current_array[m*cols+n] !=0){
                       continue;
                   }
                   tmp_count = tmp_count + (current_array[m*cols+n]);   //addieren der Nachbarpixel
               }
           }


           // Regeln für (tn+1) folgepixel
           // wird in next_array abgelegt
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
    *counter = *counter+1;  // erhöhen des Animationszählers um 1 bei erfolgreichem Durchschreiten der Berechnung

    // kopieren des berechneten Arrays auf den Speicher des Arrays aus der Liste
    memcpy(current_array, next_array, (get_X(list)+2)*(get_Y(list)+2)*sizeof (int ));

    // freigeben des speichers von dem lokal, temporär genutzten Arrays
    free(next_array);

// temp
/*
    printf("_____________________\n");


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", current_array[i * cols + j]);
        printf("\n");
    }
        printf("counter:%d",*counter);
*/
}




