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

void read_settings(list_header *list,char* path){
    FILE *file;
    file = fopen(path,"r");

    char * line = NULL;
    size_t len = 0;
    ssize_t read;



    // Fehlererkennung
    unsigned long length = strlen(path);
    const char *last_four = &path[length-4];           //Bestimmung letzte 4 Zeichen des Dateinamens


    if(strcmp(last_four,".txt") != 0){
        fprintf(stderr,"\nfile is no .txt\n");
        return;
    }

    perror("config");

    if(file == NULL){
        fprintf( stderr, "\nfile (%s) doesn't exist\n",path);
        return;
    }


    while ((read = getline(&line, &len, file)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        fscanf();


    }






}