#define _CRT_SECURE_NO_WARNINGS
#include "files_utils.h"
#include "misc.h"
#include "use_cases.h"
#include "help_utils.h"
#include "adts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#include <limits.h>


void method1() {
    //inicijalizujFajoveZaDemo();
    printf("Method 1 called.\n");
}

void method2() {
    funcMisc();
    printf("Method 2 called.\n");
}

void method3() {
    printf("%s", vratiDanasnjiDatum());
    printf("Method 3 called.\n");
}

void method4() {
    printf("Method 4 called.\n");
}

void method5() {
    printf("Method 5 called.\n");
}

void method6() {
    printf("Method 6 called.\n");
}

int main() {
    //method6();
    //printf(vratiDanasnjiDatum());
    //kreirajNovuTransakcionuDatoteku(); //TEST OK
    //char str[100];
    //fgets(str, sizeof(str), stdin);
    //validacijaBroj(str);
    //unistiPostojecuTransakcionuDatoteku();
    //inicijalizujFajoveZaDemo(1);
    //dodajNovuTransakciju();
    //dodajNovuTransakciju();
    //dodajNovuTransakciju();
    //kreirajNovuTransakcionuDatoteku();
    //prikaziSveTransakcije();
    //prikaziSveTransakcijeZaProizvod();
    //kreirajNovuMaticnuDatoteku();
    //dodajNoviProizvod();
    //dodajNoviProizvod();
    //dodajNoviProizvod();
    /*prikaziSveProizvode();
    printf("********************
    ****\n");
    SIGNAL s = obrisiProizvod();
    printf("%d\n", s);
    printf("************************\n");
    prikaziSveProizvode();*/
    //izmeniProizvod();
    //ispisiPomoc(OSN_SLUCAJ_AZURIRANJA);
    //arhivirajMaticnu();
    //prikaziSveTransakcije();
    //sumirajTransakcije();
    //procitajDatotekuPromena();
    //prikaziSveProizvode();
    //dodajNoviProizvod();
    //izmeniProizvod();
    //dodajNovuTransakciju();
    //SIGNAL s = azurirajMaticnuDatoteku();
    //printf("%d\n", s);
    //prikaziIzvestajPromena();
    //printf("leleeee\n");
    //prikaziSveProizvode();
    //kreirajNovuMaticnuDatoteku();
    //kreirajNovuMaticnuDatoteku();
    //int i = 0;
    //while (i < 3) {
    //    dodajNoviProizvod();
    //    i++;
    //}
    //kreirajNovuTransakcionuDatoteku();
    //int i = 0;
    //while (i < 4) {
    //    dodajNovuTransakciju();
    //    i++;
    //}
    //printf("************************\n");
    //prikaziSveProizvode();
    //printf("************************\n");
    //azurirajMaticnuDatoteku();
    //printf("************************\n");
    //prikaziSveProizvode();
    //prikaziIzvestajGreskaProizvod();
    return 0;
}

/*
#include <unistd.h>
#include <limits.h>

int main() {
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}
*/