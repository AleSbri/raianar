#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "lib.h"
#include "queue.h"
#include "utente.h"

int main(int argc, char const *argv[]) {

    int scelta;
    char newMeta[30];
    char username[30];
    char password[16];
    Queue shortestDistance;
    Queue cheapestRoute;
    Tratta pathPrice;
    Tratta pathDistance;
    FILE *f1, *f2;


    Utente utenti = NULL;
    Meta mete = NULL;
    mete = initGrafo(f1, f2, mete);

    utenti = inserisciUtente(utenti, "test2", "root"); // Utente di prova
    utenti->punti = 30.00;

    do {
        msgBenvenuto();
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            do {
                menuAdmin();
                scanf("%d", &scelta);

                if(scelta == 1){
                    system("cls");
                    printf("Ecco una lista delle destinazioni gia' esistenti:\n\n");
                    stampaMete(mete);
                    printf("\n\nNome destinazione da aggiungere: ");
                    scanf("%s", newMeta);
                    mete = aggiungiMeta(mete, newMeta);
                    stampaMete(mete);
                    printf("\n");
                    system("pause");
                    continue;
                } else if(scelta == 2) {
                    char dest[30];
                    char part[30];
                    int km;
                    double price;

                    system("cls");
                    printf("Ecco una lista delle citta' gia' esistenti:\n\n");
                    stampaMete(mete);

                    do {
                    printf("\n\nInserisci la citta' di partenza: ");
                    scanf("%s", part);
                        if(!checkMetaExist(mete, part)){
                            printf("La citta' di partenza inserita non esiste, riprova");
                        }
                    }while(!checkMetaExist(mete, part));

                    stampaVoli(mete,part);

                    Meta temp = NULL;
                    temp = searchMeta(mete,part);

                    do {
                    printf("\n\nInserisci la citta' d' arrivo: ");
                    scanf("%s", dest);
                        if(!checkMetaExist(mete, dest)){
                            printf("La citta' d' arrivo inserita non esiste, riprova");
                        }
                        if(strcmp(part,dest) == 0) {
                            printf("La citta' d'arrivo non può essere uguale alla citta' di partenza, riprova!");
                        }
                        if(checkTrattaExists(temp->rotta,dest)) {
                            printf("La citta' d'arrivo e' gia' raggiunbile, riprova!");
                        }
                    } while(!checkMetaExist(mete, dest) || strcmp(part,dest) == 0 || checkTrattaExists(temp->rotta,dest));

                    do {
                        printf("Inserisci la distanza in km: ");
                        scanf("%d", &km);
                        printf("Inserisci il prezzo del volo: ");
                        scanf("%lf", &price);
                        if(km <= 0 || price <= 0){
                            printf("Distanza o costo errati, riprova\n");
                        }
                    }while(km <= 0 || price <= 0);
                        mete = aggiungiTrattaToGraph(mete, part, dest, km, price);
                        printf("Volo inserito con successo!\n");
                        printf("\n");
                        system("pause && cls");
                } else if(scelta == 3) {
                    char dest[30];
                    char part[30];

                    printf("Ecco una lista delle citta' gia' esistenti:\n\n");
                    stampaMete(mete);
                    Meta temp;

                    do{
                    printf("\n\nInserisci la citta' di partenza da cui vuoi rimuovere un volo: ");
                    scanf("%s", part);
                    temp = NULL;

                        if(!checkMetaExist(mete, part)){
                            printf("La citta' di partenza inserita non esiste, riprova!");
                        } else {
                            temp = searchMeta(mete,part);
                                if(isEmptyTratta(temp->rotta)) {
                                    printf("La citta' non ha collegamenti da rimuovere, riprova!");
                                }
                        }
                    }while(!checkMetaExist(mete, part) || isEmptyTratta(temp->rotta));

                    system("cls");
                    printf("\nEcco una lista delle tratte gia' esistenti:\n\n");
                    stampaVoli(mete, part);

                    do{
                    printf("\n\nInserisci la citta' di arrivo da rimuovere: ");
                    scanf("%s", dest);
                        if(!checkMetaExist(mete, dest)){
                            printf("La citta' d' arrivo inserita non esiste, riprova");
                        }
                    }while(!checkMetaExist(mete, dest));

                    mete = eliminaTratta(mete, part, dest);
                    system("pause");
                }
                else if(scelta == 0) break;
                else{
                    printf("Inserimento non valido, riprova\n");
                    continue;
                }
            } while (1);
            break;
        case 2:;
            int choice;
            do{
                printf("Username: \n>");
                scanf("%s", username);
                printf("Password: \n>");
                scanf("%s", password);

                if(login(utenti, username, password)){
                    printf("Accesso effettuato!\n\n");
                    system("pause");
                    break;
                } else {
                    system("cls");
                    printf("Errore nell'accesso\n[0] Indietro\n[1] Riprova\n>");
                    scanf("%d", &choice);
                    if(choice == 0) break;
                    else continue;
                }
            } while (1);
            if(choice == 0) {
                choice = 1;
                break;
            }
            do {
                menuUtente(username);
                scanf("%d", &scelta);

                if(scelta == 0) break;

                if(scelta == 1){
                    system("cls");
                    printf("Ecco una lista delle tue prenotazioni:\n\n");
                    stampaPrenotazioniUtente(utenti, username);
                    printf("\n");
                    system("pause");
                }
                if(scelta == 2){
                    stampaPuntiUtente(utenti, username);
                    system("pause");
                }
                if(scelta == 3){
                    char part[30];
                    system("cls");

                    do {
                    printf("Ecco una lista di citta' da cui puoi imbarcarti con la nostra compagnia\n\n");
                    stampaMete(mete);
                    printf("\n\nInserisci la citta' di partenza: ");
                    scanf("%s", part);
                        if(!checkMetaExist(mete, part)) {
                            printf("\nLa citta' di partenza inserita non esiste, riprova!\n\n");
                            system("pause && cls");
                            continue;
                        } else {
                            Meta temp = searchMeta(mete,part);
                            if(isEmptyTratta(temp->rotta)) {
                                printf("\nQuesta citta' non ha collegamenti, riprova!\n\n");
                                system("pause && cls");
                                continue;
                            }
                        }
                        break;
                    }while(1);

                    do {
                        printf("[1] Scegli la tua destinazione\n");
                        printf("[2] Raianar consiglia...\n");
                        printf("[0] Indietro\n>");

                        scanf("%d", &scelta);

                        if(scelta == 0) break;

                        if(scelta == 1) {
                            char dest[30];
                            char c;
                            char a;
                            do {
                                system("cls");
                                printf("Ecco una lista di citta'che puoi raggiungere volando con noi!\n\n");
                                stampaMete(mete);
                                printf("\n");
                                printf("\nDove vuoi andare?\n");
                                printf("> ");
                                scanf("%s", dest);

                                                            /* Gestione degli errori */

                                if(!checkMetaExist(mete,dest)) {
                                    printf("\nLa destinazione inserita non esiste, riprova!\n\n");
                                    system("pause");
                                    continue;
                                }
                                if(!isRaggiungibile(mete,dest)) {
                                    printf("\nLa destinazione inserita non e' raggiungibile, riprova!\n\n");
                                    system("pause");
                                    continue;
                                }
                                if(strcmp(part,dest) == 0) {
                                    printf("\nLa destinazione non puo' essere uguale alla partenza, riprova!\n\n");
                                    system("pause");
                                    continue;
                                }
                                /*---------------------------------------------------------------------------*/

                                shortestDistance = NULL;
                                pathDistance = NULL;
                                shortestDistance = dijkstraDistance(mete, part);
                                pathDistance = shortestPath(pathDistance, shortestDistance, part, dest);

                                if(trattaLen(pathDistance) < 2) {
                                  printf("\nNon ho trovato percorsi che raggiungono %s, prova a cambiare il tuo itinerario\n\n",dest);
                                  system("pause && cls");
                                  break;
                                }

                                printf("\nEcco il percorso disponibile piu' breve\n\n");
                                stampaPath(pathDistance);
                                printf("\nIl prezzo e' %.2lf$\n", calcolaTotalePrice(pathDistance));
                                printf("La distanza totale e' %dKm", calcolaTotaleDistance(pathDistance));
                                printf("\n\n");

                                cheapestRoute = NULL;
                                pathPrice = NULL;
                                cheapestRoute = dijkstraPrice(mete, part);
                                pathPrice = shortestPath(pathPrice, cheapestRoute, part, dest);
                                printf("\nEcco il percorso disponibile piu' economico\n\n");
                                stampaPath(pathPrice);
                                printf("\nIl prezzo e' %.2lf$\n", calcolaTotalePrice(pathPrice));
                                printf("La distanza totale e' %dKm", calcolaTotaleDistance(pathPrice));
                                printf("\n\n");

                                do {
                                    printf("vuoi procedere all'acquisto? Y/N\n");
                                    scanf(" %c",&a);
                                    a = toupper(a);
                                    c = toupper(c);

                                    if(a == 'N') {
                                        system("cls");
                                        break;
                                    }

                                    printf("[1] Prenota volo piu' breve\n");
                                    printf("[2] Prenota volo piu' economico\n ");
                                    scanf("%d", &choice);

                                    if (checkPunti(utenti,username)) {
                                        stampaPuntiUtente(utenti, username);
                                        printf("Vuoi utilizzare i tuoi punti? Y/N\n> ");
                                        scanf(" %c", &c);
                                        c = toupper(c);
                                        if(c == 'Y' && choice == 1) {
                                            effettuaPrenotazioneDecrement(utenti, pathDistance, username);
                                            printf("Prenotazione effettuata con successo\n\n");
                                            updateRank(mete,dest);
                                        }
                                        else if (c == 'Y' && choice == 2) {
                                            effettuaPrenotazioneDecrement(utenti,pathPrice,username);
                                            printf("Prenotazione effettuata con successo\n\n");
                                            updateRank(mete,dest);
                                        }
                                        else if (c == 'N' && choice == 1) {
                                            effettuaPrenotazioneIncrement(utenti, pathDistance, username);
                                            printf("Prenotazione effettuata con successo\n\n");
                                            updateRank(mete,dest);
                                        }
                                        else if (c == 'N' && choice == 2) {
                                            printf("Prenotazione effettuata con successo\n\n");
                                            updateRank(mete,dest);
                                        }
                                    } else {
                                            if(choice == 1) {
                                                effettuaPrenotazioneIncrement(utenti, pathDistance, username);
                                                printf("Prenotazione effettuata con successo\n\n");
                                                updateRank(mete,dest);
                                            }
                                            else if (choice == 2) {
                                                effettuaPrenotazioneIncrement(utenti, pathPrice, username);
                                                printf("Prenotazione effettuata con successo\n\n");
                                                updateRank(mete,dest);
                                            }
                                        }
                                        system("pause && cls");
                                        break;
                                    }while(1);
                                    if(a == 'N') break;
                                    break;
                                }while (1);
                            }
                            if(scelta == 2){
                                system("cls");
                                printf("La meta piu' economica da %s e':\n\n", part);
                                stampaMetaPiuEconomica(mete, part);
                                printf("\n");

                                printf("La meta piu' gettonata da %s e'\n\n", part);
                                mostRankedCity(mete, part);
                                printf("\n");
                                system("pause && cls");
                                continue;
                            }
                        }while(1);
                    }
            }while(1);
            break;
        case 3:
        do {
            system("cls");
            printf("Inserici Username: ");
            scanf("%s", username);

            if(utenteAlreadyExistException(utenti,username)) {
                printf("\nIl nome utente e' gia' stato utilizzato, riprova!\n\n");
                system("pause && cls");
                continue;
            }

            printf("Inserisci password [compresa tra 4 e 16 caratteri]: ");
            scanf("%s", password);
            if(passwordLenghtException(password)) {
                registrati(utenti,username,password);
                printf("\nRegistrazione effettuata con successo!\n\n");
                system("pause");
                break;
            } else {
                printf("\nOPS! c'e' stato un errore...\n");
                system("pause");
            }
        } while (1);
            break;
        case 4:
            stampaReport(mete);
            system("pause");
            break;
        default:
            return 0;
        }
    } while(1);
}
