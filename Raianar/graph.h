#ifndef GRAFO
#define GRAFO

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct tratta {
    char destinazione[30];
    int distanza;
    double price;
    struct tratta *next;
}tratta;

typedef struct tratta *Tratta;

typedef struct meta {
    char city[30];
    int rank;
    struct meta *next;
    Tratta rotta;
}meta;

typedef struct meta *Meta;

Tratta eliminaDalleTratte(Tratta,char*);
Tratta inserisciTratta(Tratta,char*,int,double);
Tratta creaNodoTratta(char*,int,double);
Tratta searchMin(Tratta);

Meta initGrafo(FILE*,FILE*,Meta);
Meta searchMeta(Meta,char*);
Meta creaNodoMeta(char*);
Meta aggiungiTrattaToGraph(Meta,char*,char*,int,double);
Meta aggiungiMeta(Meta, char*);
Meta eliminaTratta(Meta, char*, char*);

bool metaIsEmpty(Meta);
bool isEmptyTratta(Tratta);
bool checkMetaExist(Meta,char*);
bool isRaggiungibile(Meta, char*);
bool checkTrattaExists(Tratta, char*);
int trattaLen(Tratta);

void stampaVoli(Meta, char*);
void stampaReport(Meta);
void stampaMete(Meta);
void stampaTratta(Tratta);

#endif
