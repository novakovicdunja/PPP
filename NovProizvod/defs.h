#pragma once

#ifndef DEFS_H
#define DEFS_H
#define MBS 10
#define MAXNLENGTH 9
#define MAXNAMELENGTH 15
#define MAX_BUFFER_SIZE 1024

typedef struct proizvod {
	unsigned Id;
	char     Naziv[MAXNAMELENGTH];
	unsigned Kolicina;
} PROIZVOD;

typedef enum promena {
	IZLAZ = -1,
	ULAZ = 1
} PROMENA;

typedef enum slucajazuriranja {
	O_NAMA,
	O_AZURIRANJU_SERIJSKE,
	OSN_SLUCAJ_AZURIRANJA,
	NEPOSTOJECA_KOLICINA,
	NOV_PROIZVOD,
	NEPOSTOJECI_PROIZVOD,
	SVEOBUHVATNI_SLUCAJ

} SLUCAJAZURIRANJA;

typedef struct transakcija {
	unsigned Id;
	PROMENA  Promena;
	unsigned Kolicina;
} TRANSAKCIJA;

typedef enum tipDatoteke {
	MATICNA,
	SUMTRANS,
	IZVPROMENA,
	ERR_KOL,
	ERR_PRO,
	NOV_PRO
} TIPDATOTEKE;


typedef enum signal {
	ERR = -2,
	WRN,
	END,
	OK,
	NO_ACTION
} SIGNAL;

typedef struct returnMessage {
	SIGNAL signal;
	const char* message;
} RETURNMESSAGE;

typedef SIGNAL FUNKCIJA(void);
typedef FUNKCIJA* NAREDBA;
typedef struct {
	int br_stavki;
	char* naslov;
	char* tekst;
	NAREDBA naredba[MBS];
} MENI;
#endif