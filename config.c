/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Konfigurationsdatei-Modul
 */

#include "config.h"


// für fopen, getline, fscanf, fclose:
#include <stdio.h>
// für strncmp und memset:
#include <string.h>
// für malloc, calloc und atoi:
#include <stdlib.h>
// Config und Dateiarbeit Funktionen
#define _GNU_SOURCE

long s_to_ms (float* f){
    long f_l = (long)f;
    f_l = f_l*1000;
    return f_l;

}

int field_content_conversion(char c) {
    if (c=='x') return 1;
    if (c=='.') return 0;

};


void read_settings(list_header *list,char* path){
    int* x = (int*) malloc(sizeof (int));
    int* y = (int*) malloc(sizeof (int));
    int* an_counter = (int*) malloc(sizeof (int));
    int* an_max = (int*) malloc(sizeof (int));
    long* delay = (long*) malloc(sizeof (long));


    FILE *file;
    file = fopen(path,"r");

    char * line = NULL;
    char string[256];
    char string1[256];
    char empty[1] = "";
    char puffer[256];
    int integer = 0;
    float f = 0;
    int puffer_reached = 0;
    int puffer_rows = 0;
    size_t len = 0;
    ssize_t read;






    // Fehlererkennung
    unsigned long length = strlen(path);
    const char *last_four = &path[length-4];           //Bestimmung letzte 4 Zeichen des Dateinamens


    if(strcmp(last_four,".txt") != 0){
        fprintf(stderr,"\nfile is no .txt\n");
        return;
    }



    if(file == NULL){
        fprintf( stderr, "\nfile (%s) doesn't exist\n",path);
        return;
    }

    //Ende Fehlererkennung

    while ((read = getline(&line, &len, file)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);

        integer = 0;

        sscanf(line, "%s %i", &string[0],&integer);

        if (strcmp(line,"\n")==0 && puffer_reached==1) {         //Prüfen auf Ende des Dokuments

            int *array = new_array(list);
            int cols = get_X(list)+2;
            int rows = get_Y(list)+2;
            int fields = (cols)*(rows);

            int puffer_size = (int) strlen(puffer);
            int puffer_cols = puffer_size/puffer_rows;

            int space_l_r = (cols-puffer_cols)/2;
            int space_t_b = (rows-puffer_rows)/2;

            int i,j;
            int index=space_t_b*rows+2*space_l_r;
            int field_content;

            memset(list,0, fields);

            if (((fields-puffer_size)%2)==1){
                fprintf(stderr, "\n Mittige Platzierung des Puffers nicht möglich.\n");
                exit(1);
            }

            for (i=0;i<puffer_rows;i++) {
                index=index+i*2*space_l_r+i*puffer_cols;
                for (j=0;j<puffer_cols;j++) {
                    field_content= field_content_conversion(puffer[i*puffer_cols+j-1]);
                    array[index+j]=field_content;
                }

            }

            set_array(list, array);


        };

        if (strcmp(line,"\n")==0) continue;         //Leere Zeile überspringen

        if(strncmp(string,"Zeilen",6)==0) {
            set_Y(list, &integer);
            printf("%i", get_Y(list));
        }
        else if(strncmp(string,"Spalten",7)==0) {
            set_X(list,&integer);
            printf("%i", get_X(list));
        }
        else if(strncmp(string,"Schritt:",8)==0) {
            set_animation_counter(list, &integer);
            printf("%i",get_animation_counter(list));
        }
        else if(strncmp(string,"Schritte",8)==0) {
            set_animation_maxC(list, &integer);
            printf("%i", get_animation_maxC(list));
        }
        else if(strncmp(string,"Pause",5)==0) {
            sscanf(line, "%f", &f);
            set_delay(list, s_to_ms(&f));
            printf("%ld", get_delay(list));
        }
        else if(strncmp(string, "Animations-Puffer",16)==0) {
            puffer_reached = 1;
            continue;
        }

        if (puffer_reached==1) {                           //Animations-Puffer wurde erreicht
            strcat(puffer,string);                //zusammenfügen der Einzelnen Datei-Puffer Zeilen
            puffer_rows = puffer_rows+1;
            printf("\n %s", puffer);
        }

        //fscanf(line, "%i", &integer);
        printf("\n %s,%i",string,integer);




    }

    perror("\n config");





}

