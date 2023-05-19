#pragma once
#include "defs.h"
#include <stdbool.h>

#ifndef ADTS_H
#define ADTS_H

typedef struct cvor CVOR;
typedef CVOR* PCVOR;
struct cvor {
    TRANSAKCIJA Transakcija;
    PCVOR sledeci;
};

bool postojiUListi(PCVOR glava, unsigned int id);

int prebrojElementeListe(PCVOR glava);

void ubaciNaPocetak(PCVOR* glava, TRANSAKCIJA transakcija);

#endif // !ADTS_H
