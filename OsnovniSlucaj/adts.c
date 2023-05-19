#include "adts.h"
#include <stdio.h>
#include <stdbool.h>

bool postojiUListi(PCVOR glava, unsigned int id) {
    while (glava != NULL) {
        if (glava->Transakcija.Id == id) {
            return true;
        }
        glava = glava->sledeci;
    }
    return false;
}

int prebrojElementeListe(PCVOR glava) {
    PCVOR pom = glava;
    int brojac = 0;
    while (pom != NULL) {
        brojac++;
        pom = pom->sledeci;
    }
    return brojac;
}

void ubaciNaPocetak(PCVOR* glava, TRANSAKCIJA transakcija) {
    PCVOR novi;
    novi = malloc(sizeof(CVOR));
    novi->Transakcija = transakcija;
    novi->sledeci = *glava;
    *glava = novi;
}