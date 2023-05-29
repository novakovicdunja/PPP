#define _CRT_SECURE_NO_WARNINGS
#include "use_cases.h"
#include<stdio.h>
#include "defs.h"
#include "misc.h"
#include "files_utils.h"
#include "use_cases.h"
#include <stdbool.h>
#include <string.h>

SIGNAL kreirajNovuTransakcionuDatoteku() {
    bool postoji = postojiDatoteka(transakcionaDatoteka);
    char c;
    if (postoji) {
        printf("U folderu sa podacima vec postoji transakciona datoteka.\n");
        do
        {
            printf("Da li zelite da je obrisete i kreirate novu transakcionu datoteku? (D/N)? ");
            c = getc(stdin);
            ocistiBuffer();
        } while (!validacijaDaNe(c));
        if (bezAkcije(c)) {
            return NO_ACTION;
        }
    }
    return kreirajNovuDatoteku(transakcionaDatoteka);
}

SIGNAL unistiPostojecuTransakcionuDatoteku() {
    char c;
    do
    {
        printf("Da li ste sigurni? (D/N)? ");
        c = getc(stdin);
        ocistiBuffer();
    } while (!validacijaDaNe(c));
    if (bezAkcije(c)) {
        return NO_ACTION;
    }
    return unistiDatoteku(transakcionaDatoteka);
}

SIGNAL dodajNovuTransakciju() {
    TRANSAKCIJA transakcija;
    char id[MAXNLENGTH];
    char promena;
    char kolicina[MAXNLENGTH];
    if (!postojiDatoteka(transakcionaDatoteka)) {
        return ERR;
    }
    do
    {
        printf("Unesi ID: ");
        fgets(id, sizeof(id), stdin);
    } while (!validacijaBroj(id));
    do
    {
        printf("Unesi promenu (U/I): ");
        promena = getc(stdin);
        ocistiBuffer();
    } while (!validacijaUlazIzlaz(promena));
    do
    {
        printf("Unesi kolicinu: ");
        fgets(kolicina, sizeof(kolicina), stdin);
    } while (!validacijaBroj(kolicina));
    transakcija.Id = konverzijaStr2Uint(id);
    transakcija.Promena = (promena == 'u' || promena == 'U') ? 1 : -1;
    transakcija.Kolicina = konverzijaStr2Uint(kolicina);
    return dodajNoviRedTransakciona(transakcija);
}

SIGNAL prikaziSveTransakcije() {
    return prikaziTransakcije();
}

SIGNAL prikaziSveTransakcijeZaProizvod() {
    char id[MAXNLENGTH];
    do
    {
        printf("Unesi ID: ");
        fgets(id, sizeof(id), stdin);
    } while (!validacijaBroj(id));
    return prikaziTransakcijeZaProizvod(konverzijaStr2Uint(id));
}

SIGNAL kreirajNovuMaticnuDatoteku() {
    bool postoji = postojiDatoteka(maticnaDatoteka);
    char c;
    if (postoji) {
        printf("U folderu sa podacima vec postoji maticna datoteka.\n");
        do
        {
            printf("Da li zelite da je obrisete i kreirate novu maticnu datoteku? (D/N)? ");
            c = getc(stdin);
            ocistiBuffer();
        } while (!validacijaDaNe(c));
        if (bezAkcije(c)) {
            return NO_ACTION;
        }
    }
    return kreirajNovuDatoteku(maticnaDatoteka);
}

SIGNAL unistiPostojecuMaticnuDatoteku() {
    char c;
    do
    {
        printf("Da li ste sigurni? (D/N)? ");
        c = getc(stdin);
        ocistiBuffer();
    } while (!validacijaDaNe(c));
    if (bezAkcije(c)) {
        return NO_ACTION;
    }
    return unistiDatoteku(maticnaDatoteka);
}

SIGNAL dodajNoviProizvod() {
    PROIZVOD proizvod;
    char id[MAXNLENGTH];
    char naziv[MAXNAMELENGTH];
    char kolicina[MAXNLENGTH];
    if (!postojiDatoteka(maticnaDatoteka)) {
        return ERR;
    }
    do
    {
        printf("Unesi ID: ");
        fgets(id, sizeof(id), stdin);
    } while (!validacijaBroj(id));
    do
    {
        printf("Unesi naziv proizvoda: ");
        fgets(naziv, sizeof(naziv), stdin);
        naziv[strlen(naziv) - 1] = '\0';
    } while (!validacijaNaziv(naziv));
    do
    {
        printf("Unesi kolicinu: ");
        fgets(kolicina, sizeof(kolicina), stdin);
    } while (!validacijaBroj(kolicina));
    proizvod.Id = konverzijaStr2Uint(id);
    strcpy(proizvod.Naziv, naziv);
    proizvod.Kolicina = konverzijaStr2Uint(kolicina);
    SIGNAL s = dodajNoviRedMaticna(proizvod);
    if (s != OK) {
        return s;
    }
    return sortirajMaticnuDatoteku();
}

SIGNAL prikaziSveProizvode() {
    return prikaziProizvode();
}

SIGNAL obrisiProizvod() {
    char id[MAXNLENGTH];
    do
    {
        printf("Unesi ID: ");
        fgets(id, sizeof(id), stdin);
    } while (!validacijaBroj(id));
    if (!postojiRed(maticnaDatoteka, konverzijaStr2Uint(id))) {
        printf("U maticnoj datoteci ne postoji proizvod sa unesenim id.");
        return WRN;
    }
    return obrisiRedMaticna(konverzijaStr2Uint(id));
}

SIGNAL prikaziJedanProizvod() {
    char id[MAXNLENGTH];
    do
    {
        printf("Unesi ID: ");
        fgets(id, sizeof(id), stdin);
    } while (!validacijaBroj(id));
    return prikaziProizvod(konverzijaStr2Uint(id));
}

SIGNAL izmeniProizvod() {
    PROIZVOD proizvod;
    char id[MAXNLENGTH];
    do
    {
        printf("Unesi ID: ");
        fgets(id, sizeof(id), stdin);
    } while (!validacijaBroj(id));
    if (!postojiRed(maticnaDatoteka, konverzijaStr2Uint(id))) {
        printf("U maticnoj datoteci ne postoji proizvod sa unesenim id.");
        return WRN;
    }
    char naziv[MAXNAMELENGTH];
    char kolicina[MAXNLENGTH];
    do
    {
        printf("Unesi naziv proizvoda: ");
        fgets(naziv, sizeof(naziv), stdin);
        naziv[strlen(naziv) - 1] = '\0';
    } while (!validacijaNaziv(naziv));
    do
    {
        printf("Unesi kolicinu: ");
        fgets(kolicina, sizeof(kolicina), stdin);
    } while (!validacijaBroj(kolicina));
    proizvod.Id = konverzijaStr2Uint(id);
    strcpy(proizvod.Naziv, naziv);
    proizvod.Kolicina = konverzijaStr2Uint(kolicina);
    return azurirajRedMaticna(proizvod);
}

SIGNAL azurirajMaticnuDatoteku() {
    if (!postojiDatoteka(maticnaDatoteka) || !postojiDatoteka(transakcionaDatoteka)) {
        return ERR;
    }
    SIGNAL s = sumirajTransakcije();
    if (s != OK) return s;
    s = dodajNoveProizvode();
    if (s != OK) return s;
    s = azurirajMaticnuPremaTransakcionoj();
    if (s != OK) return s;
    s = arhivirajMaticnu();
    if (s != OK) return s;
    prikaziIzvestajPromena();
    prikaziIzvestajNovProizvod();
    prikaziIzvestajGreskaKolicina();
    prikaziIzvestajGreskaProizvod();
    return s;
}