#pragma once

#ifndef FILES_UTILS_H
#define FILES_UTILS_H

#include "defs.h"
#include "adts.h"
#include <stdbool.h>


extern const char* maticnaDatoteka;
extern const char* transakcionaDatoteka;
extern const char* reportFolder;
extern const char* errorFolder;
extern const char* oldFolder;
extern const char* demoFolder;
extern const char* demoMaticnaDatoteka;
extern const char* tempDatoteka;

SIGNAL inicijalizujFajoveZaDemo(int);

const char* vratiPutanjuDatoteke(TIPDATOTEKE tipDatoteke);

const char* vratiPutanjuTransakcioneDatotekeZaDemo(int brojDemoSlucaja);

bool postojiDatoteka(const char* putanja);

SIGNAL ispisiDatoteku(const char* putanja);

SIGNAL prepisiDatoteku(const char* izvornaPutanja, const char* ciljnaPutanja);

SIGNAL spremiMaticnuTransakcionuDatotekuDemo(int brojDemoa);

SIGNAL prepisiMaticnuDemo();

SIGNAL prepisiTransakcionuDemo(int);

SIGNAL kreirajNovuDatoteku(const char* putanja);

SIGNAL unistiDatoteku(const char* putanja);

SIGNAL dodajNoviRedTransakciona(TRANSAKCIJA transakcija);

SIGNAL prikaziTransakcije();

SIGNAL prikaziTransakcijeZaProizvod(unsigned int id);

SIGNAL dodajNoviRedMaticna(PROIZVOD proizvod);

SIGNAL prikaziProizvode();

int uporediProizvode(const void* a, const void* b);

SIGNAL sortirajMaticnuDatoteku();

bool postojiRed(const char* putanja, unsigned int id);

SIGNAL obrisiRedMaticna(unsigned int id);

SIGNAL prikaziProizvod(unsigned int id);

SIGNAL azurirajRedMaticna(PROIZVOD izmenjeniProizvod);

SIGNAL arhivirajMaticnu();

SIGNAL sumirajTransakcije();

SIGNAL napuniDatotekuPromena(PCVOR glava);

SIGNAL sortirajDatotekuPromena();

void procitajDatotekuPromena();

SIGNAL azurirajMaticnuPremaTransakcionoj();

void prikaziIzvestajPromena();

const char* vratiImeNovogProizvoda(unsigned int id);

SIGNAL dodajNoveProizvode();

void prikaziIzvestajNovProizvod();


#endif