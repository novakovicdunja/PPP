#pragma once

#ifndef DEFS_H
#define DEFS_H

#define MAXNLENGTH 9
#define MAXNAMELENGTH 15

typedef struct proizvod {
	unsigned Id;
	char     Naziv[MAXNAMELENGTH];
	unsigned Kolicina;
} PROIZVOD;

typedef enum promena {
	IZLAZ = -1,
	ULAZ = 1
} PROMENA;

typedef struct transakcija {
	unsigned Id;
	PROMENA  Promena;
	unsigned Kolicina;
} TRANSAKCIJA;

typedef enum tipDatoteke {
	MATICNA,
	TRANSAKCIONA,
	SUMARNA,
	ERR_KOL,
	ERR_PRO
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

#endif