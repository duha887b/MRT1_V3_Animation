/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Grafikausgabe-Modul
 */

#include "gfx.h"
#include "graphic.h"
//für tobi
// für vorgegebene Grafik Funktionen grafik_paint_point() und andere:
#include "graphic.h"
#include "runtime_data.h"

void init_frame(list_header* list){
    grafik_init_window();
    grafik_create_paint_area(1, get_X(list)+1,1, get_Y(list)+1, get_X(list), get_Y(list)); // ZEichenfläche initialisieren



}


void print_animation_buffer(list_header*list) {

    int* current_array = get_array(list);
    int* animationspuffer = new_array(list);

    memcpy(animationspuffer, current_array, (get_X(list)+2)*(get_Y(list)+2)*sizeof (int ));

    int cols = get_X(list) + 2;
    int rows = get_Y(list) + 2;
    color_name_t color;

    grafik_lock_for_painting();

    for (int y = 0; y != get_Y(list)+1; y++) {
        for(int x = 0; x != get_X(list)+1; x++) {

            if(animationspuffer[y * cols + x]==1){
                color = Golden_Fizz;
            } else if (animationspuffer[y * cols + x]==0){
                color = Rainforest;
            } else{
                fprintf(stderr,"can't select color");
                color = Brown;
            }


            grafik_paint_point(x,y,color);

        }
    }
    grafik_unlock_and_show();
    free(animationspuffer);

}

