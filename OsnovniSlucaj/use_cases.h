#pragma once

#ifndef USE_CASES_H
#define USE_CASES_H

#include "files_utils.h"
#include "defs.h"

SIGNAL kreirajNovuTransakcionuDatoteku();
SIGNAL unistiPostojecuTransakcionuDatoteku();

SIGNAL dodajNovuTransakciju();

SIGNAL prikaziSveTransakcije();

SIGNAL prikaziSveTransakcijeZaProizvod();

SIGNAL kreirajNovuMaticnuDatoteku();

SIGNAL unistiPostojecuMaticnuDatoteku();

SIGNAL dodajNoviProizvod();

SIGNAL prikaziSveProizvode();

SIGNAL obrisiProizvod();

SIGNAL prikaziJedanProizvod();

SIGNAL izmeniProizvod();

SIGNAL azrurirajMaticnuDatoteku();

#endif // !USE_CASES_H
