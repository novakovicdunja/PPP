#define _CRT_SECURE_NO_WARNINGS
#include "files_utils.h"
#include "misc.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>




const char* maticnaDatoteka = "../DATA/maticna.dat";
const char* transakcionaDatoteka = "../DATA/transakciona.dat";
const char* reportFolder = "../RPT/";
const char* errorFolder = "../ERR/";
const char* oldFolder = "../DATA/OLD/";
const char* demoFolder = "../DEMO/";
const char* demoMaticnaDatoteka = "../DEMO/maticna.dat";
const char* tempDatoteka = "../DATA/temp.dat";

const char* vratiPutanjuTransakcioneDatotekeZaDemo(int brojDemoSlucaja) {
    static char imeTransakcioneDatoteke[100];  // Buffer to store the concatenated string
    const char* folder = "SLUC_";
    const char* imeDatoteke = "transakciona.dat";
    sprintf(imeTransakcioneDatoteke, "%s%s%d%s%s", demoFolder, folder, brojDemoSlucaja, "/", imeDatoteke);
    return imeTransakcioneDatoteke;
}

const char* vratiImeDatoteke(TIPDATOTEKE tipDatoteke) {
    static char imeDatoteke[60];  // Buffer to store the concatenated string
    const char* datum = vratiDanasnjiDatum();
    switch (tipDatoteke)
    {
    case MATICNA:
        sprintf(imeDatoteke, "%s%s%s", "mat_", datum, ".dat");
        break;
    case TRANSAKCIONA:
        sprintf(imeDatoteke, "%s%s%s", "tran_", datum, ".dat");
        break;
    case SUMARNA:
        sprintf(imeDatoteke, "%s%s%s", "prom_", datum, ".txt");
        break;
    case ERR_KOL:
        sprintf(imeDatoteke, "%s%s%s", "err_kol_", datum, ".txt");
        break;
    case ERR_PRO:
        sprintf(imeDatoteke, "%s%s%s", "err_pro_", datum, ".txt");
        break;
    default:
        break;
    }
    return imeDatoteke;
}


SIGNAL inicijalizujFajoveZaDemo(int brojDemoa) {
    int mat = prepisiMaticnuDemo();
    int tr = prepisiTransakcionuDemo(brojDemoa);
    if (mat + tr == 2) return OK;
    
    return ERR;
}


SIGNAL prepisiDatoteku(const char* izvornaPutanja, const char* ciljnaPutanja) {
    FILE* izvornaDatoteka = fopen(izvornaPutanja, "rb");
    if (izvornaDatoteka == NULL) {
        return ERR;
    }
    FILE* ciljnaDatoteka = fopen(ciljnaPutanja, "wb");
    if (ciljnaDatoteka == NULL) {
        fclose(izvornaDatoteka);
        return ERR;
    }

    int c;
    while ((c = fgetc(izvornaDatoteka)) != EOF) {
        fputc(c, ciljnaDatoteka);
    }
    fclose(izvornaDatoteka);
    fclose(ciljnaDatoteka);
    return OK;
}

SIGNAL spremiMaticnuTransakcionuDatotekuDemo(int brojDemoa) {
    SIGNAL prepisiMaticnu = prepisiDatoteku(demoMaticnaDatoteka, maticnaDatoteka);
    if (prepisiMaticnu != OK) {
        return prepisiMaticnu;
    }
    const char* demoTransakcionaDatoteka = vratiPutanjuTransakcioneDatotekeZaDemo(brojDemoa);
    SIGNAL prepisiTransakcionu = prepisiDatoteku(demoTransakcionaDatoteka, transakcionaDatoteka);
    if (prepisiTransakcionu != OK) {
        return prepisiTransakcionu;
    }
    return OK;
}

SIGNAL prepisiMaticnuDemo() {
    if (!postojiDatoteka(maticnaDatoteka)) {
        SIGNAL prepisiMaticnu = prepisiDatoteku(demoMaticnaDatoteka, maticnaDatoteka);
        if (prepisiMaticnu != OK) {
            return prepisiMaticnu;
        }
    }
    return OK;
}

SIGNAL prepisiTransakcionuDemo(int brojDemoa) {
    if (!postojiDatoteka(transakcionaDatoteka)) {
        const char* demoTransakcionaDatoteka = vratiPutanjuTransakcioneDatotekeZaDemo(brojDemoa);
        SIGNAL prepisiTransakcionu = prepisiDatoteku(demoTransakcionaDatoteka, transakcionaDatoteka);
        if (prepisiTransakcionu != OK) {
            return prepisiTransakcionu;
        }
    }
    return OK;
}

SIGNAL kreirajNovuDatoteku(const char* putanja) {
    FILE* datoteka = fopen(putanja, "wb");
    if (datoteka != NULL) {
        fclose(datoteka);
        return OK;
    }
    return ERR;
}

SIGNAL unistiDatoteku(const char* putanja) {
    if (remove(putanja) == 0) {
        return OK;
    }
    return ERR;
}

bool postojiDatoteka(const char* putanja) {
    FILE* datoteka = fopen(putanja, "r");
    if (datoteka != NULL) {
        fclose(datoteka);
        return true;
    }
    return false;
}

SIGNAL dodajNoviRedTransakciona(TRANSAKCIJA transakcija) {
    FILE* datoteka = fopen(transakcionaDatoteka, "ab");
    if (datoteka == NULL) return ERR;
    int brUpis = fwrite(&transakcija, sizeof(TRANSAKCIJA), 1, datoteka);
    fclose(datoteka);
    if (brUpis < 1) return ERR;
    return OK;
}

SIGNAL prikaziTransakcije() {
    TRANSAKCIJA transakcija;
    FILE* datoteka = fopen(transakcionaDatoteka, "rb");
    if (datoteka == NULL) return ERR;
    while (fread(&transakcija, sizeof(TRANSAKCIJA), 1, datoteka) == 1) {
        printf("%-8d%-12s%-8d\n", transakcija.Id, transakcija.Promena == 1 ? "ULAZ" : "IZLAZ", transakcija.Kolicina);
    }
    fclose(datoteka);
    return OK;
}

SIGNAL prikaziTransakcijeZaProizvod(unsigned int id) {
    TRANSAKCIJA transakcija;
    FILE* datoteka = fopen(transakcionaDatoteka, "rb");
    if (datoteka == NULL) return ERR;
    while (fread(&transakcija, sizeof(TRANSAKCIJA), 1, datoteka) == 1) {
        if (transakcija.Id == id) {
            printf("%-8d%-12s%-8d\n", transakcija.Id, transakcija.Promena == 1 ? "ULAZ" : "IZLAZ", transakcija.Kolicina);
            break;
        }
    }
    fclose(datoteka);
    return OK;
}

SIGNAL sortirajMaticnuDatoteku() {
    FILE* datoteka = fopen(maticnaDatoteka, "rb");
    if (datoteka == NULL) {
        return ERR;
    }

    // broj redova u datoteci
    fseek(datoteka, 0, SEEK_END);
    long datotekaVel = ftell(datoteka);
    rewind(datoteka);
    int brLin = datotekaVel / sizeof(PROIZVOD);

    // alociramo niz u velicini datoteke
    PROIZVOD* proizvodi = (PROIZVOD*)malloc(brLin * sizeof(PROIZVOD));
    fread(proizvodi, sizeof(PROIZVOD), brLin, datoteka);
    fclose(datoteka);

    // sortiranje
    qsort(proizvodi, brLin, sizeof(PROIZVOD), uporediProizvode);

    // Write the sorted proizvodi back to the file
    datoteka = fopen(maticnaDatoteka, "wb");
    if (datoteka == NULL) {
        return ERR;
    }
    int rezUpis = fwrite(proizvodi, sizeof(PROIZVOD), brLin, datoteka);
    fclose(datoteka);
    free(proizvodi);
    return rezUpis == brLin ? OK : ERR;
}

SIGNAL prikaziProizvode() {
    PROIZVOD proizvod;
    FILE* datoteka = fopen(maticnaDatoteka, "rb");
    if (datoteka == NULL) return ERR;
    while (fread(&proizvod, sizeof(PROIZVOD), 1, datoteka) == 1) {
        printf("%-8d%-12s%-8d\n", proizvod.Id, proizvod.Naziv, proizvod.Kolicina);
    }
    fclose(datoteka);
    return OK;
}

SIGNAL prikaziProizvod(unsigned int id) {
    PROIZVOD proizvod;
    FILE* datoteka = fopen(maticnaDatoteka, "rb");
    if (datoteka == NULL) return ERR;
    while (fread(&proizvod, sizeof(PROIZVOD), 1, datoteka) == 1) {
        if (proizvod.Id == id) {
            printf("%-8d%-12s%-8d\n", proizvod.Id, proizvod.Naziv, proizvod.Kolicina);
            break;
        }
    }
    fclose(datoteka);
    return OK;
}


int uporediProizvode(const void* a, const void* b) {
    const PROIZVOD* prA = (const PROIZVOD*)a;
    const PROIZVOD* prB = (const PROIZVOD*)b;
    return prA->Id - prB->Id;
}

SIGNAL dodajNoviRedMaticna(PROIZVOD proizvod) {
    FILE* datoteka = fopen(maticnaDatoteka, "ab");
    if (datoteka == NULL) return ERR;
    int brUpis = fwrite(&proizvod, sizeof(PROIZVOD), 1, datoteka);
    fclose(datoteka);
    if (brUpis < 1) return ERR;
    return OK;
}

bool postojiRed(const char* putanja, unsigned int id) {
    PROIZVOD proizvod;
    FILE* datoteka = fopen(putanja, "rb");
    //sumnjivo
    if (datoteka == NULL) {
        return false;
    }
    while (fread(&proizvod, sizeof(PROIZVOD), 1, datoteka) == 1) {
        if (proizvod.Id == id) return true;
    }
    return false;
}

SIGNAL obrisiRedMaticna(unsigned int id) {
    PROIZVOD proizvod;
    FILE* maticna = fopen(maticnaDatoteka, "rb");
    FILE* temp = fopen(tempDatoteka, "wb");
    if (maticna == NULL || temp == NULL) {
        return ERR;
    }
    while (fread(&proizvod, sizeof(PROIZVOD), 1, maticna) == 1) {
        if (proizvod.Id != id) {
            if (fwrite(&proizvod, sizeof(PROIZVOD), 1, temp) < 1) return ERR;
        }
    }
    fclose(temp);
    fclose(maticna);
    SIGNAL s = prepisiDatoteku(tempDatoteka, maticnaDatoteka);
    if (s != OK) {
        return s;
    }
    return unistiDatoteku(tempDatoteka);
}

SIGNAL azurirajRedMaticna(PROIZVOD izmenjeniProizvod) {
    PROIZVOD proizvod;
    FILE* maticna = fopen(maticnaDatoteka, "rb");
    FILE* temp = fopen(tempDatoteka, "wb");
    if (maticna == NULL || temp == NULL) {
        return ERR;
    }
    while (fread(&proizvod, sizeof(PROIZVOD), 1, maticna) == 1) {
        if (proizvod.Id == izmenjeniProizvod.Id) {
            proizvod = izmenjeniProizvod;
        }
        if (fwrite(&proizvod, sizeof(PROIZVOD), 1, temp) < 1) return ERR;
    }
    fclose(temp);
    fclose(maticna);
    SIGNAL s = prepisiDatoteku(tempDatoteka, maticnaDatoteka);
    if (s != OK) {
        return s;
    }
    return unistiDatoteku(tempDatoteka);
}