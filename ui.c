/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Nutzerinteraktions-Modul
 */

#include "ui.h"

// für vorgegebene UI Funktionen: grafik_user_input()
# include "graphic.h"

// für die Funktion `exit`
#include <stdlib.h>

#include <unistd.h>
#include "engine.h"

int ui(list_header* list){


    while (grafik_user_input(10) > Fehler);

    switch (grafik_user_input(100))
    {
        case Beenden:
            exit(0); //beenden auf q

        case Pause:
            // TODO func

        case Schritt:
            // TODO func


        default:

            if(get_animation_maxC(list)== *get_animation_counter(list)){
                return 1;
            }

            usleep(get_delay(list));
            cal_nextAnimaionStep(list);

            return 0;

    }

}

// Funktionen um Nutzerinteraktionen zu behandeln
