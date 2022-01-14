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
#include "gfx.h"

void ui(list_header* list){


    while (grafik_user_input(10) > Fehler);

    switch (grafik_user_input(100))
    {
        case Beenden:

            exit(0); //beenden auf q

        case Pause:
        {
            while(1) //Pause mit Leertaste
            {

                while (grafik_user_input(10) > Fehler);

                switch (grafik_user_input(100)) {
                    case Beenden:       //beenden des Programmes in der Pause
                        exit(0);
                    case Pause:
                        return; //mit Leertaste weitermachen
                    case Schritt:
                        if(get_animation_maxC(list)== *get_animation_counter(list)){
                            continue;
                        }
                        cal_nextAnimaionStep(list);
                        print_animation_buffer(list);
                        continue; // in Pause nächsten Animationsschritt zeigen

                }



            }
        }
        case Schritt:

            {
                cal_nextAnimaionStep(list); // nächsten Animtionsschritt
                while(1)
                {
                    while (grafik_user_input(10) > Fehler);

                    switch (grafik_user_input(100))
                    {
                        case Beenden: // in Pause Programm beenden
                            exit(0);
                        case Pause: // in Pause Programm fortsetzen
                            return;
                        case Schritt:
                            if(get_animation_maxC(list)== *get_animation_counter(list)){
                                continue;
                            }
                            cal_nextAnimaionStep(list);
                            print_animation_buffer(list);
                            continue; // in Pause nächsten Animationsschritt anzeigen
                    }



                }
            }




        default:

            if(get_animation_maxC(list)== *get_animation_counter(list)){
                return ;
            }

            usleep(get_delay(list));
            cal_nextAnimaionStep(list);

            return ; // normales Ablaufen der Animation

    }

}

// Funktionen um Nutzerinteraktionen zu behandeln
