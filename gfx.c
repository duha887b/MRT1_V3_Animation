/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Grafikausgabe-Modul
 */

#include "gfx.h"

// für vorgegebene Grafik Funktionen grafik_paint_point() und andere:
#include "graphic.h"
#include "runtime_data.h"

// Funktionen zur Grafikausgabe


void print_animation_buffer(list_header list)
 {
    grafik_create_paint_area();
    grafik_lock_for_painting();

    int* animationspuffer = get_array(list);
int cols = get_X(list) + 2;
int rows = get_Y(list) + 2;

    for (int x; x < get_X(list); x++) {
        for(int y; y < get_Y(list); y++) {
            grafik_paint_point(x, y, animationspuffer[x * (get_X(list) + 2) + y]);
        }
    }

    grafik_unlock_and_show();
}