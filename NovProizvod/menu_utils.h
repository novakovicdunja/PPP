#pragma once

#ifndef MENU_UTILS
#define MENU_UTILS
#include <stdio.h>
#include "defs.h"
#include "help_utils.h"
#include "use_cases.h"
#include "files_utils.h"

SIGNAL izvrsi(MENI meni);
int izaberi_naredbu(MENI meni);
void obradi_signal(SIGNAL signal);

SIGNAL radSaTransakcionomDatotekom(void);

SIGNAL radSaMaticnomDatotekom(void);

SIGNAL pomoc(void);

SIGNAL kraj(void);

SIGNAL krajRadaSaTransakcionomDatotekom(void);

SIGNAL krajRadaSaMaticnomDatotekom(void);

SIGNAL kraj_pomoc(void);

SIGNAL oAzuriranjuSerijskeBiblioteke(void);

SIGNAL demo(void);

SIGNAL oNama(void);

SIGNAL krajDemo(void);

SIGNAL osnovniSlucajHelp(void);

SIGNAL nepostojecaKolicinaHelp(void);

SIGNAL novProizvodHelp(void);

SIGNAL nepostojeciProizvodHelp(void);

SIGNAL sveobuhvatniSlucajHelp(void);


static MENI glavni_meni = {
        .br_stavki = 4,
        .naslov = "\n************************************************************************\n"\
                  "*  Aplikacija: ASD\n"\
                  "*  Opis      : Azuriranje serijske (sortirane redne) datoteke\n"\
                  "*  Upotreba  : asd.exe [-d[1|2|3|4|5]]\n"\
                  "*  Upotreba  : asd.exe [-d[1|2|3|4|5]]\n"\
                  "*                1 - demo za prvi slucaj azuriranja,\n"\
                  "*                2 - demo za drugi slucaj azuriranja, ...\n"\
                  "*  Datum     : %s.\n"\
                  "*  Autor     : Dunja Novakovic, dn20180067@student.fon.bg.ac.rs\n"\
                  "************************************************************************\n"\
                  "\n===============\n GLAVNI MENI \n===============\n",
        .tekst = " 0. Kraj rada\n\n 1. Rad sa transakcionom datotekom\n 2. Rad sa maticnom datotekom\n 3. Pomoc\n",
        .naredba = { kraj, radSaTransakcionomDatotekom, radSaMaticnomDatotekom, pomoc }
};

static MENI transakciona_datoteka_meni = {
        .br_stavki = 6,
        .naslov = "\n===============\n MENI Transakciona datoteka\n===============\n",
        .tekst = " 0. Povratak\n\n 1. Create\n 2. Drop\n 3. Insert\n 4. Select All\n 5. Select Id\n",
        .naredba = { krajRadaSaTransakcionomDatotekom, kreirajNovuTransakcionuDatoteku,
                     unistiPostojecuTransakcionuDatoteku,dodajNovuTransakciju,
                     prikaziSveTransakcije, prikaziSveTransakcijeZaProizvod}
};

static MENI maticna_datoteka_meni = {
        .br_stavki = 9,
        .naslov = "\n===============\n MENI Maticna datoteka\n===============\n",
        .tekst = " 0. Povratak\n\n 1. Create\n 2. Drop\n 3. Insert\n 4. Delete\n 5. Update All\n 6. Update Id\n 7. Select All\n 8. Select Id\n",
        .naredba = { krajRadaSaMaticnomDatotekom, kreirajNovuMaticnuDatoteku,
                     unistiPostojecuMaticnuDatoteku,dodajNoviProizvod,
                     obrisiProizvod, azurirajMaticnuDatoteku,
                     azurirajRedMaticna, prikaziSveProizvode, prikaziJedanProizvod}
};


static MENI pomoc_meni = {
        .br_stavki = 4,
        .naslov = "\n===============\n MENI Pomoc\n===============\n",
        .tekst = " 0. Povratak\n\n 1. O azuriranju serijske datoteke\n 2. Demo\n 3. O nama\n",
        .naredba = { kraj_pomoc, oAzuriranjuSerijskeBiblioteke,
                     demo,oNama}
};


static MENI demo_meni = {
        .br_stavki = 6,
        .naslov = "\n===============\n MENI Demo\n===============\n",
        .tekst = " 0. Povratak\n\n 1. Osnovni slucaj\n 2. Nepostojeca kolicina\n 3. Nov proizvod\n 4. Nepostojeci proizvod\n 5. Sveobuhvatni slucaj\n",
        .naredba = { krajDemo, osnovniSlucajHelp,
                     nepostojecaKolicinaHelp,novProizvodHelp,
                     nepostojeciProizvodHelp, sveobuhvatniSlucajHelp}
};

#endif
