#ifndef CODA
#define CODA
#include "graph.h"

typedef struct coda {
    char name[30];
    char pred[30];
    int distance;
    double price;
    struct coda *next;
}coda;

typedef struct coda *Queue;

Queue inizializzaCoda(Meta,Queue);
Queue creaNodo(char*,char*,int,double);
Queue enqueue(Queue,char*,char*,int,double);
Queue dequeue(Queue,char*);
Queue dijkstraDistance(Meta, char*);
Queue dijkstraPrice(Meta, char*);
Queue searchMinQueueDistance(Queue);
Queue searchMinQueuePrice(Queue);
void stampaMetaPiuEconomica(Meta, char*);
Tratta shortestPath(Tratta,Queue,char*,char*);


bool modifyQueueDistance(Queue,char*,int);
bool modifyQueuePrice(Queue, char*,float);
bool modifyQueuePred(Queue , char *, char *);
bool isEmptyQueue(Queue);

void searchNodoSrc(Queue,char*);
double calcolaTotalePrice(Tratta t);
int calcolaTotaleDistance(Tratta t);

#endif