#include "queue.h"
#define FLT_MAX 1000000.00

Queue creaNodo(char *name, char *pred,int distance, double prezzo) {
    Queue temp;
    temp = (Queue)malloc(sizeof(struct coda));
    strcpy(temp->name,name);
    strcpy(temp->pred,pred);
    temp->distance = distance;
    temp->price = prezzo;
    temp->next = NULL;
    return temp;
}

Queue enqueue(Queue q,char *name, char *pred, int distance, double prezzo) {
    if(!q) return creaNodo(name,pred,distance,prezzo);
    q->next = enqueue(q->next,name,pred,distance,prezzo);
    return q;
}

Queue dequeue(Queue q, char *name) {
    if(!isEmptyQueue(q) && strcmp(q->name,name) != 0) 
        q->next = dequeue(q->next,name);
    else {
        Queue temp = q->next;
        free(q);
        return temp;
    }
    return q;
}


Queue inizializzaCoda(Meta m,Queue q) {
    if(!metaIsEmpty(m)) {
        q = enqueue(q,m->city,m->city,INT_MAX,FLT_MAX);
        q->next = inizializzaCoda(m->next,q->next);
    }
    return q;
}


Queue searchMinQueueDistance(Queue q) {
    Queue temp;
    int min = INT_MAX;

    while(!isEmptyQueue(q)) {
        if(min > q->distance) { 
            min = q->distance;
            temp = q;
        }
        q = q->next;
    }
    return temp;
}

Queue searchMinQueuePrice(Queue q) {
    Queue temp;
    float min = FLT_MAX;

    while(!isEmptyQueue(q)) {
        if(min > q->price) { 
            min = q->price;
            temp = q;
        }
        q = q->next;
    }
    return temp;
}

void stampaMetaPiuEconomica(Meta m, char *city){
    if(!metaIsEmpty(m)){
        if(strcmp(m->city, city) == 0){
            if(!isEmptyTratta(m->rotta)){
                Tratta t = searchMin(m->rotta);
                printf("%s", t->destinazione);
                printf("\n");
            }
        }else stampaMetaPiuEconomica(m->next, city);
    }
}

bool isEmptyQueue(Queue q) {
    return q == NULL;
}

Queue dijkstraDistance(Meta g, char *partenza) {
    Queue Q = NULL; // Coda Iniziale
    Queue S = NULL; // Coda Finale
    Queue shortestPath = NULL; //Elementi della Coda minimi
    Meta temp = NULL; // nodo d'appoggio

    Q = inizializzaCoda(g,Q);
    searchNodoSrc(Q,partenza); // trova partenza e inizializza la partenza a 0
    while(!isEmptyQueue(Q)) {
        shortestPath = searchMinQueueDistance(Q); //trova la distanza minima nella coda
        temp = searchMeta(g,shortestPath->name); //recupero il vertice corrispondente al nodo con la minor distanza
        while(temp->rotta) { //esploro gli archi
            if(modifyQueueDistance(Q,temp->rotta->destinazione,temp->rotta->distanza + shortestPath->distance)){ //rilassamento 
                S = enqueue(S,temp->rotta->destinazione,temp->city,temp->rotta->distanza,temp->rotta->price);
            if(modifyQueuePred(S,temp->rotta->destinazione,temp->city)){ // controllo sui predecessori da aggiornare
              S=dequeue(S,temp->rotta->destinazione);  
            }
          }
            temp->rotta = temp->rotta->next;
        }
        Q = dequeue(Q,temp->city); 
    }
return S;
}

Queue dijkstraPrice(Meta g, char *partenza) {
    Queue Q = NULL; // Coda Iniziale
    Queue S = NULL; // Coda Finale
    Queue shortestPath = NULL; //Elementi della Coda minimi
    Meta temp = NULL; // nodo d'appoggio

    Q = inizializzaCoda(g,Q);
    searchNodoSrc(Q,partenza); // trova partenza e inizializza la partenza a 0
    while(!isEmptyQueue(Q)) {
        shortestPath = searchMinQueuePrice(Q); //trova il prezzo minimo nella coda
        temp = searchMeta(g,shortestPath->name); //recupero il vertice corrispondente al nodo con il minor prezzo
        while(temp->rotta) { //esploro gli archi
            if(modifyQueuePrice(Q,temp->rotta->destinazione,temp->rotta->price + shortestPath->price)){ //rilassamento
                S = enqueue(S,temp->rotta->destinazione,temp->city,temp->rotta->distanza,temp->rotta->price);
                if(modifyQueuePred(S,temp->rotta->destinazione,temp->city)){ // controllo sui predecessori da aggiornare
                    S=dequeue(S,temp->rotta->destinazione);
                }
            }
            temp->rotta = temp->rotta->next;
        }
        Q = dequeue(Q,temp->city);
    }
    return S;
}

Tratta shortestPath(Tratta t,Queue q, char *src,char *dst) {
    Queue temp = q;
    while(!isEmptyQueue(q)) {
        if(strcmp(q->name,dst) == 0) {
            t = inserisciTratta(t,q->name,q->distance,q->price); 
            t = shortestPath(t,temp,src,q->pred);
        }
        q = q->next;
    }
    if(strcmp(src,dst) == 0)
        t = inserisciTratta(t,src,0,0.0);
    return t;
}

bool modifyQueueDistance(Queue q, char *target,int peso) {
    if(!isEmptyQueue(q)) {
        if(strcmp(q->name,target) == 0) {
            if(q->distance > peso) {
                q->distance = peso;
                return true;
            }else return false;
        } else modifyQueueDistance(q->next,target,peso);
    }
}

bool modifyQueuePrice(Queue q, char *target, float peso){
    if(!isEmptyQueue(q)) {
        if(strcmp(q->name,target) == 0) {
            if(q->price > peso) {
                q->price = peso;
                return true;
            }else return false;
        } else modifyQueuePrice(q->next,target,peso);
    }
}

bool modifyQueuePred(Queue q, char *target, char *pred) {
    if(!isEmptyQueue(q)) {
        if(strcmp(q->name,target) == 0) {
            if(strcmp(pred,q->pred) != 0) {
              if(strcmp(target,q->pred)!=0){
                strcpy(q->pred,pred);
                return true;
              }
            }else return false;
        } else modifyQueuePred(q->next,target,pred);
    }
}

void searchNodoSrc(Queue q, char *name) {
    if(!isEmptyQueue(q)) {
        if(strcmp(q->name,name) == 0) {
            q->distance = 0;
            q->price = 0.0;
        } else searchNodoSrc(q->next,name);
    }
}

double calcolaTotalePrice(Tratta t){
    if(!isEmptyTratta(t)){
        return t->price + calcolaTotalePrice(t->next);
    } else return 0.0;
}

int calcolaTotaleDistance(Tratta t){
    if(!isEmptyTratta(t)){
        return t->distanza + calcolaTotaleDistance(t->next);
    } else return 0;
}