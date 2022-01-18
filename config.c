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
#include <math.h>

int field_content_conversion(char c) {
    if (c=='x') return 1;
    if (c=='.') return 0;

    return 0;
}

long getdelay_ms (char string[]){       //Bestimmen des Delays(Pause) in ms
    int tmp=0,i=0;
    float f=0;
    long f_l=0;

    while (tmp<1) {
        int cmp = (unsigned char) string[i];
        if (cmp>47 && cmp<58) {tmp=1;break;}        //überprüfen ob char eine Zahl ist
        i++;
    }
    const char *end_float = &string[i];    //string vor Pause entfernen
    sscanf(end_float,"%f",&f);            //float aus übrigem string bestimmen

    if (f==0) {
    	int f_i = 0;
    	printf(end_float);
    	sscanf(end_float,"%i",&f_i);
    	f_i = f_i*1000;
    	f_l = (long) f_i;
    	return f_l;
    }


    f=roundf((f*1000));                            //s to ms
    f_l = (long) f;

    return f_l;
}

void read_settings(list_header *list,char* path){
    int* x = (int*) malloc(sizeof (int));
    int* y = (int*) malloc(sizeof (int));
    int* an_counter = (int*) malloc(sizeof (int));
    int* an_max = (int*) malloc(sizeof (int));
    long* delay = (long*) malloc(sizeof (long));

    FILE *file;
    file = fopen(path,"r");

    char * line = NULL;
    char *string;
    string = malloc(1);

    char *puffer;
    int integer = 0;
    int puffer_reached = 0;
    int puffer_rows = 0;
    size_t len = 0;
    ssize_t line_length;

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


    while ((line_length=getline(&line, &len, file)) != -1) {


        integer = 0;

        string = realloc(string,line_length+1);

        sscanf(line, "%s %i", &string[0],&integer);


        if (strcmp(line,"\n")==0 && puffer_reached==1) {         //Prüfen auf Ende des Dokuments

            int *array = new_array(list);
            int cols = get_X(list)+2;                           //Spalten des Bilds + 2
            int rows = get_Y(list)+2;                           //Zeilen des Bilds + 2
            int fields = (cols)*(rows);                         //Gesamtanzahl der Felder

            int puffer_size = (int) strlen(puffer);           //Größe des Puffers(aus Datei)
            int puffer_cols = puffer_size/puffer_rows;           //Spalten des Puffers

            int space_l_r = (cols-puffer_cols)/2;                //Platz jeweils am linken und rechten Rand
            int space_t_b = (rows-puffer_rows)/2;                //Platz jeweils am oberen und unteren Rand

            int i,j;
            int index=(space_t_b-1)*cols+space_l_r-1;                //start index für array
            int field_content;

            int cols_even = (cols-puffer_cols)%2;
            int rows_even = (rows-puffer_rows)%2;
            int transfer = 0;

            memset(array,0, fields);                   //array auf 0 initialisieren

            if (((fields-puffer_size)%2)==1 || (cols_even==1) || (rows_even==1)){
                fprintf(stderr, "\n\n Mittige Platzierung des Puffers nicht möglich.\n");
            }

            if (cols_even == 1) transfer=1;

            for (i=0;i<puffer_rows;i++) {                           //Iteration über Reihen des Puffers
                index=index+puffer_cols+2*space_l_r+transfer;            //Sprung um 2*Platz-links/rechts + Spalten des Puffers
                for (j=0;j<puffer_cols;j++) {                       //Iteration über Spalten des Puffers
                    field_content= field_content_conversion(puffer[i*puffer_cols+j]);
                    array[index+j+1]=field_content;
                }
            }

            set_array(list, array); //array zu Laufzeit Daten hinzufügen



            int m,n;

            for (m=0;m<rows;m++) {
            	printf("\n");
            	for (n=0;n<cols;n++){
            		printf("%i ",array[m*cols+n]);
            	}

            }


        }


        if (strcmp(line,"\n")==0) continue;         //Leere Zeile überspringen

        if(strncmp(string,"Zeilen",6)==0) {
            *y = integer;
            set_Y(list, y);
        }
        else if(strncmp(string,"Spalten",7)==0) {
            *x = integer;
            set_X(list,x);
            //printf("x", get_X(list));
        }
        else if(strncmp(string,"Schritt:",8)==0) {
            *an_counter = integer,
            set_animation_counter(list, an_counter);
            //printf("counter", get_animation_counter(list));
        }
        else if(strncmp(string,"Schritte",8)==0) {
            *an_max = integer;
            set_animation_maxC(list, an_max);
            //printf("x", get_animation_maxC(list));
        }
        else if(strncmp(string,"Pause",5)==0) {
            long tmp = getdelay_ms(line);
            *delay= tmp;
            set_delay(list, delay);
            //printf("delay", get_delay(list));
        }
        else if(strncmp(string, "Animations-Puffer",16)==0) {
            puffer_reached = 1;
            puffer=malloc((get_X(list)+2)*(get_Y(list)+2));
            //printf("\npuffer_reached:%i",puffer_reached);
            continue;
        }

        if (puffer_reached==1) {                           //Animations-Puffer wurde erreicht
            strcat(puffer,string);              //zusammenfügen der Einzelnen Datei-Puffer Zeilen
            puffer_rows = puffer_rows+1;
            printf("\nAnimationspuffer:%s",puffer);
        }
    }

     perror("\n config");


}

