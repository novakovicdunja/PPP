#pragma once

#include "defs.h"
#include <stdbool.h>

#ifndef MISC_H
#define MISC_H

void funcMisc();

const char* vratiDanasnjiDatum();

bool validacijaDaNe(char c);

bool bezAkcije(char c);

bool validacijaBroj(const char str[MAXNLENGTH]);

bool validacijaId(const char str[MAXNLENGTH]);

unsigned int konverzijaStr2Uint(const char str[]);

bool validacijaUlazIzlaz(char c);

void ocistiBuffer();

bool validacijaNaziv(const char naziv[MAXNAMELENGTH]);

#endif