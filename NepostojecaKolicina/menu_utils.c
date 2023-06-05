#pragma once
#include "menu_utils.h"
#include "defs.h"
#include "use_cases.h"
#include "files_utils.h"
#include "misc.h"
#include <stdio.h>
#include <stdlib.h>

SIGNAL izvrsi(MENI meni)
{
    int izbor = izaberi_naredbu(meni);
    SIGNAL sig = meni.naredba[izbor]();
    obradi_signal(sig);
    return sig;
}

int get_int(char* prompt, int dg, int gg) {
    char string[99];
    int number;
    char* strptr;
    do {
        fputs(prompt, stdout);
        fgets(string, 99, stdin);
        number = strtol(string, &strptr, 10);
    } while (number < dg || number > gg);
    return number;
}

int izaberi_naredbu(MENI meni)
{
    char* datum = vratiDanasnjiDatum();
    system("cls");
    //puts(meni.naslov);
    printf(meni.naslov, datum);
    puts(meni.tekst);
    char prompt[22] = " Vas izbor [0..%d] -> ";
    snprintf(prompt, 22, prompt, meni.br_stavki - 1);
    int i = get_int(prompt, 0, meni.br_stavki - 1);
    return (i);
}

void obradi_signal(SIGNAL signal)
{
    switch (signal) {
    case ERR: fputs("\n>>> GRESKA: program ce biti prekinut.\n", stderr);
        exit(EXIT_FAILURE);
    case WRN:
    case OK: system("pause"); break;
    case END: break;
    default: fputs("ERROR: izvrsi()", stderr);
    }
}

SIGNAL radSaTransakcionomDatotekom(void)
{
    while (izvrsi(transakciona_datoteka_meni) != END); return OK;
}

SIGNAL radSaMaticnomDatotekom(void)
{
    while (izvrsi(maticna_datoteka_meni) != END); return OK;
}

SIGNAL pomoc(void)
{
    while (izvrsi(pomoc_meni) != END); return OK;
}

SIGNAL kraj(void)
{
    fputs("\nKRAJ RADA\nCopyright (C) FON-LSI, 2019.\n", stdout); return END;
}

SIGNAL krajRadaSaTransakcionomDatotekom(void)
{
    return END;
}

SIGNAL krajRadaSaMaticnomDatotekom(void)
{
    return END;
}

SIGNAL kraj_pomoc(void)
{
    return END;
}

SIGNAL oAzuriranjuSerijskeBiblioteke(void)
{
    return ispisiDatoteku(oAzururanjuSerijskeDatotekePutanja);
}

SIGNAL demo(void)
{
    while (izvrsi(demo_meni) != END); return OK;
}

SIGNAL oNama(void)
{
    printf("Softverski inzenjer: Dunja D. Novakovic, dn20180067@student.fon.bg.ac.rs, student Informacionih sistema"\
        "i tehnologija na Fakultetu organizacionih nauka\n");
    printf("Softverski inzenjer: Sasa D. Lazarevic, lazarevic.sasa@fon.bg.ac.rs, redovni profesor"\
        " na Fakultetu organizacionih nauka\n");
    return OK;
}

SIGNAL krajDemo(void)
{
    return END;
}

SIGNAL osnovniSlucajHelp(void)
{
    return ispisiDatoteku(oAzururanjuSerijskeDatotekePutanja);
}

SIGNAL nepostojecaKolicinaHelp(void)
{
    return ispisiDatoteku(nepostojecaKolicinaPutanja);
}

SIGNAL novProizvodHelp(void)
{
    return ispisiDatoteku(novProizvodPutanja);
}

SIGNAL nepostojeciProizvodHelp(void)
{
    return ispisiDatoteku(nepostojeciProizvodPutanja);
}

SIGNAL sveobuhvatniSlucajHelp(void)
{
    return ispisiDatoteku(sveobuhvatniSlucajPutanja);
}
