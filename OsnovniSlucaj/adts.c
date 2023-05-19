#include "adts.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

void azurirajElementListe(PCVOR* glava, TRANSAKCIJA transakcija) {
    const PCVOR pom = *glava;
    while (*glava != NULL) {
        if ((*glava)->Transakcija.Id == transakcija.Id) {
            int zbir = (*glava)->Transakcija.Promena * (*glava)->Transakcija.Kolicina + transakcija.Promena * transakcija.Kolicina;
            (*glava)->Transakcija.Promena = zbir < 0 ? IZLAZ : ULAZ;
            (*glava)->Transakcija.Kolicina = abs(zbir);
            break;
        }
        (*glava) = (*glava)->sledeci;
    }
    *glava = pom;
    //PCVOR pom = malloc(sizeof(PCVOR));
    //pom->Transakcija = (*glava)->Transakcija;
    //pom->sledeci = (*glava)->sledeci;
    //while (pom != NULL) {
    //    if (pom->Transakcija.Id == transakcija.Id) {
    //        int zbir = pom->Transakcija.Promena * pom->Transakcija.Kolicina + transakcija.Promena * transakcija.Kolicina;
    //        pom->Transakcija.Promena = zbir < 0 ? IZLAZ : ULAZ;
    //        pom->Transakcija.Kolicina = abs(zbir);
    //        break;
    //    }
    //    pom = pom->sledeci;
    //}
    //free(pom);
}

void prikaziListu(PCVOR glava) {
    PCVOR tekuci;
    tekuci = glava;
    printf("\n*** Sadrzaj liste ***\n");
    while (tekuci != NULL) {
        printf("%d\t%d\t%d\n", tekuci->Transakcija.Id, tekuci->Transakcija.Promena, tekuci->Transakcija.Kolicina);
        tekuci = tekuci->sledeci;
    }
}
