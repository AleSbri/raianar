#include "utente.h"


bool utenteTreeIsEmpty(Utente u){
    return u == NULL;
}

bool prenotazioneIsEmpty(Prenotazioni p){
    return p == NULL;
}


//---------------------------------------------------------------------------------------

Prenotazioni allocaPrenotazione(Tratta q){
    Prenotazioni newPre = (Prenotazioni)malloc(sizeof(struct prenotation));
    newPre->percorsi = q;
    newPre->totale = 0;
    newPre->next = NULL;
    return newPre;
}

Prenotazioni inserisciPrenotazione(Prenotazioni p, Tratta q, double costo){
    if(prenotazioneIsEmpty(p)){
        if(!isEmptyTratta(q)){
                p = inserisciPrenotazione(p, q->next, costo);
                p = allocaPrenotazione(q);
                p->totale = costo;
            }
        }else p->next = inserisciPrenotazione(p->next, q, costo);
    return p;
}

void stampaPrenotazione(Prenotazioni p){
    if(!prenotazioneIsEmpty(p)){
        printf("\n*****************************************************************************************\n");
        stampaPath(p->percorsi);
        printf("\nIl costo totale e' %.2lf", p->totale);
        printf("\n");
        stampaPrenotazione(p->next);
    } 
}

//---------------------------------------------------------------------------------------


Utente allocaUtente(char *username, char *password){
    Utente newUser = (Utente)malloc(sizeof(struct user));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->punti = 0.0;
    newUser->viaggio = NULL;
    newUser->dx=NULL;
    newUser->sx=NULL;
    return newUser;
}

Utente inserisciUtente(Utente u,char *username, char *password){
    if(utenteTreeIsEmpty(u))
        return allocaUtente(username, password);
    
    if(strcmp(username, u->username) < 0)
        u->sx = inserisciUtente(u->sx, username, password);
    else 
        u->dx = inserisciUtente(u->dx, username, password);

    return u;
}

void effettuaPrenotazioneIncrement(Utente u,Tratta q, char *username){
    if(!utenteTreeIsEmpty(u)){
        if(strcmp(u->username, username) == 0){
                double costo = calcolaTotalePrice(q);
                u->viaggio = inserisciPrenotazione(u->viaggio, q, costo);
                u->punti += updatePuntiIncrement(q);
                printf("\nIl prezzo del volo e' %.2lf\n", costo);
        }
        else if (strcmp(username, u->username) < 0)
            effettuaPrenotazioneIncrement(u->sx, q, username);
        else if (strcmp(username, u->username) > 0)
            effettuaPrenotazioneIncrement(u->dx, q, username);
    }
}

void effettuaPrenotazioneDecrement(Utente u,Tratta q, char *username){
        if(!utenteTreeIsEmpty(u)){
        if(strcmp(u->username, username) == 0){
            double costo = updatePuntiDecrement(q, u, username);
            u->viaggio = inserisciPrenotazione(u->viaggio, q, costo);
            printf("\nIl prezzo del volo e' %.2lf\n", costo);
        }
        else if (strcmp(username, u->username) < 0)
            effettuaPrenotazioneDecrement(u->sx, q, username);
        else if (strcmp(username, u->username) > 0)
            effettuaPrenotazioneDecrement(u->dx, q, username);
    }
}

void stampaPrenotazioniUtente(Utente u, char *username){
    if(!utenteTreeIsEmpty(u)){
        if(strcmp(u->username, username) == 0){
            if(prenotazioneIsEmpty(u->viaggio)){
                printf("L'utente non ha prenotazioni\n");
            }else
                stampaPrenotazione(u->viaggio);      
        }
        else if (strcmp(username, u->username) < 0)
            stampaPrenotazioniUtente(u->sx, username);
        else if (strcmp(username, u->username) > 0)
            stampaPrenotazioniUtente(u->dx, username);
    }
}

void stampaPuntiUtente(Utente u, char *username){
        if(!utenteTreeIsEmpty(u)){
        if(strcmp(u->username, username) == 0){
            printf("Hai %.2lf punti\n", u->punti);    
        }
        else if (strcmp(username, u->username) < 0)
            stampaPuntiUtente(u->sx, username);
        else if (strcmp(username, u->username) > 0)
            stampaPuntiUtente(u->dx, username);
    }
}

double updatePuntiIncrement(Tratta q){
    double tmp = 0;
    while(!isEmptyTratta(q)){
        tmp += q->price;
        q = q->next;
    }
    return tmp*0.1;
}

double updatePuntiDecrement(Tratta q, Utente u, char *username){
        if(!utenteTreeIsEmpty(u)){
            double costo = calcolaTotalePrice(q);
            if(strcmp(u->username, username) == 0){
                    if(u->punti * 0.3 <= costo) { 
                        costo -= u->punti*0.3;                      
                        u->punti = 0;
                        return costo;
                    } else {
                        u->punti = 0;
                        return 0.0;
                    }
                }
            else if (strcmp(username, u->username) < 0)
                updatePuntiDecrement(q, u->sx, username);
            else if (strcmp(username, u->username) > 0)
                updatePuntiDecrement(q, u->dx, username);
    }
}
//---------------------------------------------------------------------------------------

bool passwordLenghtException(char *password) {
    if(strlen(password) == 0 || strlen(password) <4 || strlen(password) >= 16 )
        return false;
    return true;
}

bool utenteAlreadyExistException(Utente u,char *username){
    bool found = false;
    if(!utenteTreeIsEmpty(u)){
        if(strcmp(u->username, username) == 0){
            found = true;
        }
        else if(strcmp(username, u->username) < 0)
            found = utenteAlreadyExistException(u->sx, username);
        else if(strcmp(username, u->username) > 0)
            found = utenteAlreadyExistException(u->dx, username);
    }
    return found;
}

//----------------------------------------------------------------------------------------


bool login(Utente u, char *username, char *password) {
    bool found = false;
    if(!utenteTreeIsEmpty(u)){
        if(strcmp(u->username, username) == 0 && strcmp(u->password,password) == 0){
            found = true;
        }
        else if(strcmp(username, u->username) < 0)
            found = login(u->sx, username, password);
        else if(strcmp(username, u->username) > 0)
            found = login(u->dx, username, password);
    }
    return found;
}

bool checkPunti(Utente u, char *username) {
        bool found = false;
    if(!utenteTreeIsEmpty(u)){
        if(u->punti >= 10 && strcmp(u->username, username) == 0){
            found = true;
        }
        else if(strcmp(username, u->username) < 0)
            found = checkPunti(u->sx, username);
        else if(strcmp(username, u->username) > 0)
            found = checkPunti(u->dx, username);
    }
    return found;
}

Utente registrati(Utente u, char *username, char *password) {
        u = inserisciUtente(u,username,password);
        return u;
}
