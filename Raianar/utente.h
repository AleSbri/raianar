#ifndef USER
#define USER
#include "queue.h"
#include "lib.h"
#include <ctype.h>

typedef struct prenotation{
    Tratta percorsi;
    double totale;
    struct prenotation *next;
} prenotation;

typedef struct prenotation *Prenotazioni;

typedef struct user {
    char username[30];
    char password[16];
    float punti;
    Prenotazioni viaggio;
    struct user *dx;
    struct user *sx;
} user;

typedef struct user *Utente;

bool utenteTreeIsEmpty(Utente u);
Utente allocaUtente(char*, char*);
Utente inserisciUtente(Utente,char*, char*);

void effettuaPrenotazioneIncrement(Utente,Tratta, char*);
void effettuaPrenotazioneDecrement(Utente,Tratta, char*);
bool prenotazioneIsEmpty(Prenotazioni p);
Prenotazioni allocaPrenotazione(Tratta);
Prenotazioni inserisciPrenotazione(Prenotazioni, Tratta, double);
double updatePuntiIncrement(Tratta);
double updatePuntiDecrement(Tratta, Utente, char*);

bool utenteAlreadyExistException(Utente,char*);
bool passwordLenghtException(char*);

bool login(Utente,char*,char*);
bool checkPunti(Utente,char*);
Utente registrati(Utente,char*,char*);

void stampaPrenotazione(Prenotazioni);
void stampaPrenotazioniUtente(Utente u, char *username);
void stampaPuntiUtente(Utente, char*);

#endif