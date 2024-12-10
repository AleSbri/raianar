#include "lib.h"
#define FLT_MAX 1000000.00

void stampaPath(Tratta t) {
    if(!isEmptyTratta(t)) {
        stampaPath(t->next);
        printf("|%s %dkm $%.2f| - ", t->destinazione, t->distanza, t->price);
    }
}

void mostRankedCity(Meta m, char *src) {
    int max = 0;
    Meta tmp = m;
    char name[30];
    while(!metaIsEmpty(tmp)){
        if(strcmp(tmp->city, src) != 0){
            if(max <= tmp->rank){
                max = tmp->rank;
                strcpy(name, tmp->city);
            }
        }
        tmp = tmp->next;
    }
    printf("%s\n", name);
}

void updateRank(Meta m, char *city){
    if(!metaIsEmpty(m)){
        if(strcmp(m->city, city) == 0){
            m->rank+=1;
        }
        else updateRank(m->next, city);
    }
}

void msgBenvenuto() {
        system("cls");
        printf("------------------------------------------------------------\n");
        printf("------------------| Benvenuto in Raianar |------------------\n");
        printf("------------------------------------------------------------\n");
        printf("[1] Accesso compagnia\n");
        printf("[2] Accesso utente\n");
        printf("[3] Registrazione utente\n");
        printf("[4] Visualizza voli\n");
        printf("[0] Termina\n");
        printf("> ");
}

void menuAdmin() {
        system("cls");
        printf("[1] Aggiungi nuova destinazione\n");
        printf("[2] Aggiungi nuovo volo\n");
        printf("[3] Rimuovi volo\n");
        printf("[0] Indietro\n");
        printf("> ");
}

void menuUtente(char *username) {
        system("cls");
        printf("Benvenuto %s!\n\n", username);
        printf("[1] Visualizza le tue prenotazioni\n");
        printf("[2] Saldo punti\n");
        printf("[3] Pianifica il tuo viaggio\n");
        printf("[0] Logout\n");
        printf("> ");
}
