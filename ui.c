/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Nutzerinteraktions-Modul
 */

#include "ui.h"

// für vorgegebene UI Funktionen: grafik_user_input()
# include "graphic.h"

// für die Funktion `exit`
#include <stdlib.h>

void ui(){


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
            //delay

            return;

    }

}

// Funktionen um Nutzerinteraktionen zu behandeln
