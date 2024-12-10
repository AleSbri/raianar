#include "graph.h"

Tratta eliminaDalleTratte(Tratta t, char *city){
    if(!isEmptyTratta(t)){
        if(strcmp(t->destinazione, city) != 0) {
            t->next = eliminaDalleTratte(t->next, city);
            } else {
                Tratta tmp = t->next;
                free(t);
                printf("\nRimozione avvenuta con successo\n\n");
                return tmp;
                }
            }
    return t;
}

Tratta creaNodoTratta(char *destination, int distance,  double price) {
    Tratta temp;
    temp = (Tratta)malloc(sizeof(struct tratta));
    temp->distanza = distance;
    temp->price = price;
    strcpy(temp->destinazione,destination);
    temp->next = NULL;
    return temp;
}

Tratta inserisciTratta(Tratta t, char *destination, int distance, double price) {
    if(isEmptyTratta(t)){
        return creaNodoTratta(destination,distance,price);
    }
    else if(strcmp(destination, t->destinazione) != 0)
        t->next = inserisciTratta(t->next,destination,distance,price);
    return t;
}


Tratta searchMin(Tratta rotta) {
    Tratta temp = (Tratta)malloc(sizeof(struct tratta));
    int min = INT_MAX;
    char str[30];
    while(rotta) {
        if(min > rotta->distanza) {
            strcpy(str,rotta->destinazione);
            min = rotta->distanza;
        }
        rotta = rotta->next;
    }
    temp->distanza = min;
    strcpy(temp->destinazione,str);
    temp->next = NULL;
    return temp;
}

Meta eliminaTratta(Meta m, char *src, char*dst){
    if(!metaIsEmpty(m)){
        if(strcmp(m->city, src) == 0){
            if(!isEmptyTratta(m->rotta))
                m->rotta = eliminaDalleTratte(m->rotta, dst);
        } else
            m->next = eliminaTratta(m->next, src, dst);
    }
}

Meta searchMeta(Meta m, char *nome) {
    Meta temp = NULL;
    Tratta t = m->rotta;
    if(m) {
        if(strcmp(m->city,nome) == 0) {
            temp = aggiungiMeta(temp,m->city);
            while (t) {
                temp = aggiungiTrattaToGraph(temp,m->city,t->destinazione,t->distanza,t->price);
                t = t->next;
            }
        } else return searchMeta(m->next,nome);
    }
    return temp;
}

Meta creaNodoMeta(char *city) {
    Meta femp = (Meta)malloc(sizeof(struct meta));
    femp->rotta = NULL;
    strcpy(femp->city,city);
    femp->rank = 0;
    femp->next = NULL;
    return femp;
}

Meta aggiungiMeta(Meta m, char *city) {
    if(metaIsEmpty(m)) {
        return creaNodoMeta(city);
    }
    else if(strcmp(city, m->city) != 0)
        m->next = aggiungiMeta(m->next,city);
    return m;
}


Meta aggiungiTrattaToGraph(Meta m, char *src, char* dst, int distance, double price) {
    if(!metaIsEmpty(m)) {
        if(strcmp(m->city,src) == 0)
            m->rotta = inserisciTratta(m->rotta,dst,distance,price);
        else if(strcmp(m->city, src) != 0)
            m->next = aggiungiTrattaToGraph(m->next,src,dst,distance,price);
        }
    return m;
}

void stampaReport(Meta m) {
    if(!metaIsEmpty(m)) {
        printf("\n%s -------->",m->city);
        stampaTratta(m->rotta);
        printf("\n");
        stampaReport(m->next);
    }
}

void stampaTratta(Tratta t) {
    if(!isEmptyTratta(t)) {
        printf("|%s %dkm $%.2f| - ", t->destinazione, t->distanza, t->price);
        stampaTratta(t->next);
    } else printf("-|");
}

void stampaMete(Meta m){
    if(!metaIsEmpty(m)){
        printf("| %s |", m->city);
        stampaMete(m->next);
    }
}

void stampaVoli(Meta m, char *city){
    if(!metaIsEmpty(m)){
        if(strcmp(m->city, city) == 0){
            stampaTratta(m->rotta);
        }
        else stampaVoli(m->next, city);
    }
}

bool isEmptyTratta(Tratta t) { return t == NULL; }

bool metaIsEmpty(Meta m) { return m == NULL; }

bool checkMetaExist(Meta m, char *city) {
    if(!metaIsEmpty(m)) {
        if(strcmp(m->city,city) == 0)
            return true;
        else checkMetaExist(m->next,city);
    } else return false;
}

 Meta initGrafo(FILE *fp, FILE *fg, Meta destinazioni) {
     char src[30];
     char dst[30];
     int distance;
     double price;

     fp = fopen("mete.txt","r");

     while (!feof(fp)) {
         fscanf(fp,"%s",src);
         destinazioni = aggiungiMeta(destinazioni,src);
     }
     fclose(fp);

     fg = fopen("rotteInit.txt","r");
     while (!feof(fg)) {
         fscanf(fg,"%s %s %d %lf",src,dst,&distance,&price);
         destinazioni = aggiungiTrattaToGraph(destinazioni,src,dst,distance,price);
     }
     fclose(fg);

     return destinazioni;
 }

bool isRaggiungibile(Meta m, char *city){
    if(!metaIsEmpty(m)) {
        if(checkTrattaExists(m->rotta,city)) {
            return true;
        } else isRaggiungibile(m->next,city);
    } else return false;
}

bool checkTrattaExists(Tratta q, char *city){
    if(!isEmptyTratta(q)) {
        if(strcmp(q->destinazione,city) == 0) {
            return true;
        } else checkTrattaExists(q->next,city);
    } else return false;
}

int trattaLen(Tratta t){
  if(!isEmptyTratta(t)){
    return trattaLen(t->next) + 1;
  }else return 0;
}
