/* BOF MAIN_C
Praktikumsversuch: Einführung in die Sprache C
        Haupt-Programm
*/

#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "runtime_data.h"
#include "config.h"
#include "gfx.h"
#include "engine.h"
#include "ui.h"

// Forwarddeklaration der später definierten Hilfsfunktionen:
void goodbye_msg(void);
static void init_exit(void);

int main(void)
{
    list_header *list = new_specific_list();
    read_settings(list, "./settings-1.txt");


    init_exit();
    init_frame(list);

    while(1){
        print_animation_buffer(list);
        if(ui(list))break;

    }

    return 0;
}

// -- Hilfsfunktionen ---
static void init_exit(void)
{
    if (atexit(goodbye_msg))
    {
        fprintf(stderr, "Fehler bei Registrierung der Exitfunktion\n");
        exit(-1);
    }
}

void goodbye_msg(void)
{
    printf("MRT1, V3, Programm beendet.\n");
}

/* EOF MAIN_C */
