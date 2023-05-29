#define _CRT_SECURE_NO_WARNINGS
#include "misc.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>



void funcMisc() {
    printf("Misc");
}

const char* vratiDanasnjiDatum() {
    time_t sada = time(NULL);
    struct tm* datum = localtime(&sada);
    static char formatiranDatum[7]; // Buffer to store the formatted date
    strftime(formatiranDatum, sizeof(formatiranDatum), "%y%m%d", datum);
    return formatiranDatum;
}

bool validacijaDaNe(char c) {
    if (c == 'N' || c == 'n' || c == 'D' || c == 'd') {
        return true;
    }
    return false;
}

bool validacijaUlazIzlaz(char c) {
    if (c == 'U' || c == 'u' || c == 'I' || c == 'i') {
        return true;
    }
    return false;
}

bool validacijaNaziv(const char naziv[MAXNAMELENGTH]) {
    int i = 0;
    bool blanko = true;
    if (naziv[i] == '\0' || !isalpha(naziv[i]) || isspace(naziv[i])) return false;
    while (i < MAXNAMELENGTH) {
        if (!isspace(naziv[++i])) {
            blanko = false;
            break;
        }
    }
    return !blanko;
}

bool bezAkcije(char c) {
    if (c == 'N' || c == 'n') {
        return true;
    }
    return false;
}

bool validacijaBroj(const char str[MAXNLENGTH]) {
    //if (str[0] == '-') return false;


    //char *br;
    //char strkopija[MAXIDLENGTH]; //kopija napravljena jer je parameter const
    //a parameter je const zbog izbegavanja nestabilnosti
    //a te nestabilnosti su ...
    //strcpy(strkopija, str);
    //unsigned long number = strtoul(str, &br, 10);
    // u br se upisuje sve ono sto nije broj na kraju konverzije, pa i novi red
    // proverava se da li je u tom ostatku '\n' na prvom mestu

    //return   number >= 0 && number <= UINT_MAX && br[0] == '\n';
    char strkopija[MAXNLENGTH]; //kopija napravljena jer je parameter const
    //a parameter je const zbog izbegavanja nestabilnosti
    strcpy(strkopija, str);
    if (strlen(strkopija) > 0 && strkopija[strlen(strkopija) - 1] == '\n') {
        strkopija[strlen(strkopija) - 1] = '\0';
    }
    int i = 0;
    char c = strkopija[i];
    while (c != '\0') {
        if (isdigit(c) == 0) {
            return false;
        }
        c = strkopija[i++];
    }
    return true;
}

bool validacijaId(const char str[MAXNLENGTH]) {
    if (!validacijaBroj(str)) {
        return false;
    }
    unsigned long number = strtoul(str, NULL, 10);
    return number > 0 && number < UINT_MAX;
}

bool validacijaBroj2(const char str[MAXNLENGTH]) {
    char strkopija[MAXNLENGTH]; //kopija napravljena jer je parameter const
    //a parameter je const zbog izbegavanja nestabilnosti
    strcpy(strkopija, str);
    if (strlen(strkopija) > 0 && strkopija[strlen(strkopija) - 1] == '\n') {
        strkopija[strlen(strkopija) - 1] = '\0';
    }
    int i = 0;
    char c = strkopija[i];
    while (c != '\0') {
        if (isdigit(c) == 0) {
            return false;
        }
        c = strkopija[i++];
    }
    unsigned long number = strtoul(str, &strkopija, 10);
    return true;
}

unsigned int konverzijaStr2Uint(const char str[]) {
    return (unsigned int)strtoul(str, NULL, 10);
}

void ocistiBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Consume characters until newline or end of file is reached
    }
}