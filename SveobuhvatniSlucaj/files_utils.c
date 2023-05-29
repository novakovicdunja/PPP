#define _CRT_SECURE_NO_WARNINGS
#include "files_utils.h"
#include "misc.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "adts.h"




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

const char* vratiPutanjuDatoteke(TIPDATOTEKE tipDatoteke) {
    static char imeDatoteke[60];  // Buffer to store the concatenated string
    const char* datum = vratiDanasnjiDatum();
    switch (tipDatoteke)
    {
    case MATICNA:
        sprintf(imeDatoteke, "%s%s%s%s", oldFolder, "mat_", datum, ".dat");
        break;
    case SUMTRANS:
        sprintf(imeDatoteke, "%s%s%s%s", oldFolder, "tran_", datum, ".dat");
        break;
    case IZVPROMENA:
        sprintf(imeDatoteke, "%s%s%s%s", reportFolder, "prom_", datum, ".txt");
        break;
    case ERR_KOL:
        sprintf(imeDatoteke, "%s%s%s%s", errorFolder, "err_kol_", datum, ".txt");
        break;
    case ERR_PRO:
        sprintf(imeDatoteke, "%s%s%s%s", errorFolder, "err_pro_", datum, ".txt");
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

SIGNAL ispisiDatoteku(const char* putanja)
{
    FILE* datoteka = fopen(putanja, "r");
    if (datoteka == NULL) {
        return ERR;
    }

    char bafer[MAX_BUFFER_SIZE];
    size_t procitaniPodaci;

    while ((procitaniPodaci = fread(bafer, 1, sizeof(bafer), datoteka)) > 0) {
        fwrite(bafer, 1, procitaniPodaci, stdout);
    }

    fclose(datoteka);
    return OK;
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

    // upisi proizvode u fajl
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

int uporediTransakcije(const void* a, const void* b) {
    const TRANSAKCIJA* prA = (const TRANSAKCIJA*)a;
    const TRANSAKCIJA* prB = (const TRANSAKCIJA*)b;
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

SIGNAL arhivirajMaticnu() {
    return prepisiDatoteku(maticnaDatoteka, vratiPutanjuDatoteke(MATICNA));
}



SIGNAL sortirajDatotekuPromena() {
    FILE* datoteka = fopen(vratiPutanjuDatoteke(SUMTRANS), "rb");
    if (datoteka == NULL) {
        return ERR;
    }

    // broj redova u datoteci
    fseek(datoteka, 0, SEEK_END);
    long datotekaVel = ftell(datoteka);
    rewind(datoteka);
    int brLin = datotekaVel / sizeof(TRANSAKCIJA);

    // alociramo niz u velicini datoteke
    TRANSAKCIJA* transakcije = (TRANSAKCIJA*)malloc(brLin * sizeof(TRANSAKCIJA));
    fread(transakcije, sizeof(TRANSAKCIJA), brLin, datoteka);
    fclose(datoteka);

    // sortiranje
    qsort(transakcije, brLin, sizeof(TRANSAKCIJA), uporediTransakcije);

    // upisi proizvode u fajl
    datoteka = fopen(vratiPutanjuDatoteke(SUMTRANS), "wb");
    if (datoteka == NULL) {
        return ERR;
    }
    int rezUpis = fwrite(transakcije, sizeof(TRANSAKCIJA), brLin, datoteka);
    fclose(datoteka);
    free(transakcije);
    return rezUpis == brLin ? OK : ERR;
}

SIGNAL vratiJedinstveneTransakcija() {
    FILE* datoteka = fopen(transakcionaDatoteka, "rb");
    PCVOR glava = NULL;
    TRANSAKCIJA transakcija;
    while (fread(&transakcija, sizeof(TRANSAKCIJA), 1, datoteka) == 1) {
        if (!postojiUListi(glava, transakcija.Id)) {
            ubaciNaPocetak(&glava, transakcija);
        }
    }
    fclose(datoteka);
}

SIGNAL sumirajTransakcije() {
    FILE* datoteka = fopen(transakcionaDatoteka, "rb");
    if (datoteka == NULL) {
        return ERR;
    }
    // broj redova u datoteci
    fseek(datoteka, 0, SEEK_END);
    long datotekaVel = ftell(datoteka);
    rewind(datoteka);
    int brLin = datotekaVel / sizeof(TRANSAKCIJA);

    // alociramo niz u velicini datoteke
    TRANSAKCIJA* transakcije = (TRANSAKCIJA*)malloc(brLin * sizeof(TRANSAKCIJA));
    PCVOR glava = NULL;
    fread(transakcije, sizeof(TRANSAKCIJA), brLin, datoteka);
    for (int i = 0; i < brLin; i++)
    {
        TRANSAKCIJA t = transakcije[i];
        if (!postojiUListi(glava, t.Id)) {
            ubaciNaPocetak(&glava, t);
        }
        else {
            azurirajElementListe(&glava, t);
        }
    }
    free(transakcije);
    fclose(datoteka);

    SIGNAL s = kreirajNovuDatoteku(vratiPutanjuDatoteke(SUMTRANS));
    if (s != OK) return s;
    s = napuniDatotekuPromena(glava);
    if (s != OK) return s;
    s = sortirajDatotekuPromena();
    if (s != OK) return s;
    ocistiListu(glava);
    return OK;
}

SIGNAL napuniDatotekuPromena(PCVOR glava) {
    FILE* datoteka = fopen(vratiPutanjuDatoteke(SUMTRANS), "wb");
    TRANSAKCIJA transakcija;
    if (datoteka == NULL) {
        return ERR;
    }
    while (glava != NULL) {
        transakcija = glava->Transakcija;
        if (fwrite(&transakcija, sizeof(TRANSAKCIJA), 1, datoteka) < 1) return ERR;
        glava = glava->sledeci;
    }
    fclose(datoteka);
    return OK;
}


void procitajDatotekuPromena() {
    FILE* datoteka = fopen(vratiPutanjuDatoteke(SUMTRANS), "rb");
    TRANSAKCIJA transakcija;
    if (datoteka == NULL) {
        return;
    }
    while (fread(&transakcija, sizeof(TRANSAKCIJA), 1, datoteka) == 1) {
        printf("%-8d%-12s%-8d\n", transakcija.Id, transakcija.Promena == 1 ? "ULAZ" : "IZLAZ", transakcija.Kolicina);
    }
    fclose(datoteka);
}

SIGNAL azurirajMaticnuPremaTransakcionoj() {
    FILE* maticna = fopen(maticnaDatoteka, "rb");
    if (maticna == NULL) {
        return ERR;
    }

    // broj redova u datoteci
    fseek(maticna, 0, SEEK_END);
    long datotekaVel = ftell(maticna);
    rewind(maticna);
    int brLinMat = datotekaVel / sizeof(PROIZVOD);

    // alociramo niz u velicini datoteke
    PROIZVOD* proizvodi = (PROIZVOD*)malloc(brLinMat * sizeof(PROIZVOD));
    fread(proizvodi, sizeof(PROIZVOD), brLinMat, maticna);
    fclose(maticna);


    FILE* sumTrans = fopen(vratiPutanjuDatoteke(SUMTRANS), "rb");
    if (sumTrans == NULL) {
        return ERR;
    }

    // broj redova u datoteci
    fseek(sumTrans, 0, SEEK_END);
    datotekaVel = ftell(sumTrans);
    rewind(sumTrans);
    int brLinSumTrans = datotekaVel / sizeof(TRANSAKCIJA);

    // alociramo niz u velicini datoteke
    TRANSAKCIJA* transakcije = (TRANSAKCIJA*)malloc(brLinSumTrans * sizeof(TRANSAKCIJA));
    fread(transakcije, sizeof(TRANSAKCIJA), brLinSumTrans, sumTrans);
    fclose(sumTrans);

    FILE* izvPromena = fopen(vratiPutanjuDatoteke(IZVPROMENA), "wb");
    if (izvPromena == NULL) return ERR;
    for (int i = 0; i < brLinMat; i++)
    {
        for (int j = 0; j < brLinSumTrans; j++) {
            if (proizvodi[i].Id == transakcije[j].Id) {
                unsigned int staraKolicina = proizvodi[i].Kolicina;
                proizvodi[i].Kolicina += transakcije[j].Promena * transakcije[j].Kolicina;
                fprintf(izvPromena, "%-9d\t%-9d\t%-15s\t%-5s\t%-9d\t%-9d\n", proizvodi[i].Id, staraKolicina, proizvodi[i].Naziv, transakcije[j].Promena == ULAZ ? "+" : "-", transakcije[j].Kolicina, proizvodi[i].Kolicina);
                break;
            }
        }
    }

    fclose(izvPromena);

    //upis promena nazad u maticnu
    maticna = fopen(maticnaDatoteka, "wb");
    if (maticna == NULL) return ERR;
    int rezUpis = fwrite(proizvodi, sizeof(PROIZVOD), brLinMat, maticna);
    fclose(maticna);
    free(transakcije);
    free(proizvodi);
    return rezUpis == brLinMat ? OK : ERR;
}

void prikaziIzvestajPromena() {
    printf("\n- - - - - - - - - - - - - - - IZVESTAJ O PROMENAMA - - - - - - - - - - - - - - -\n");
    printf("%-33s\t\t%-14s\t\t%-9s\n", "Proizvod", "Promena", "Nova");
    printf("%-9s\t%-9s\t%-15s\t%-5s\t%-9s\t%-9s\n", "Id", "Kolicina", "Naziv", "Tip", "Kolicina", "kolicina");
    ispisiDatoteku(vratiPutanjuDatoteke(IZVPROMENA));
    printf("\n- - - - - - - - - - - - - - -  KRAJ IZVESTAJA  - - - - - - - - - - - - - - - - -\n");
}