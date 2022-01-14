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
            free_all(list);
            exit(0); //beenden auf q

        case Pause:
        {
            while(1)
            {
                // TODO func
                while (grafik_user_input(10) > Fehler);

                switch (grafik_user_input(100)) {
                    case Beenden:
                        exit(0);
                    case Pause:
                        return;
                    case Schritt:
                        if(get_animation_maxC(list)== *get_animation_counter(list)){
                            continue;
                        }
                        cal_nextAnimaionStep(list);
                        print_animation_buffer(list);
                        continue;

                }



            }
        }
        case Schritt:
            // TODO func
            {
                cal_nextAnimaionStep(list);
                while(1)
                {
                    while (grafik_user_input(10) > Fehler);

                    switch (grafik_user_input(100))
                    {
                        case Beenden:
                            exit(0);
                        case Pause:
                            return;
                        case Schritt:
                            if(get_animation_maxC(list)== *get_animation_counter(list)){
                                continue;
                            }
                            cal_nextAnimaionStep(list);
                            print_animation_buffer(list);
                            continue;
                    }



                }
            }




        default:

            if(get_animation_maxC(list)== *get_animation_counter(list)){
                return ;
            }

            usleep(get_delay(list));
            cal_nextAnimaionStep(list);

            return ;

    }

}

// Funktionen um Nutzerinteraktionen zu behandeln
