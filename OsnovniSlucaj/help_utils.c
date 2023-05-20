#define _CRT_SECURE_NO_WARNINGS

#include "help_utils.h"
#include "defs.h"
#include <stdio.h>


const char* oNamaPutanja = "../HELP/o_nama.txt";
const char* oAzururanjuSerijskeDatotekePutanja = "../HELP/o_azuriranju_serijske_datoteke.txt";

const char* osnovniSlucajAzuriranjaPutanja = "../HELP/osnovni_slucaj_azuriranja.txt";
const char* nepostojecaKolicinaPutanja = "../HELP/nepostojeca_kolicina.txt";
const char* novProizvodPutanja = "../HELP/nov_proizvod.txt";
const char* nepostojeciProizvodPutanja = "../HELP/nepostojeci_proizvod.txt";
const char* sveobuhvatniSlucajPutanja = "../HELP/sveobuhvatni_slucaj.txt";

SIGNAL ispisiPomoc(SLUCAJAZURIRANJA sa)
{
    switch (sa)
    {
    case O_NAMA:
        return ispisiDatoteku(oNamaPutanja);
    case O_AZURIRANJU_SERIJSKE:
        return ispisiDatoteku(oAzururanjuSerijskeDatotekePutanja);
    case OSN_SLUCAJ_AZURIRANJA:
        return ispisiDatoteku(osnovniSlucajAzuriranjaPutanja);
    case NEPOSTOJECI_PROIZVOD:
        return ispisiDatoteku(nepostojeciProizvodPutanja);
    case NOV_PROIZVOD:
        return ispisiDatoteku(novProizvodPutanja);
    case SVEOBUHVATNI_SLUCAJ:
        return ispisiDatoteku(sveobuhvatniSlucajPutanja);
    default:
        return ERR;
    }
}


