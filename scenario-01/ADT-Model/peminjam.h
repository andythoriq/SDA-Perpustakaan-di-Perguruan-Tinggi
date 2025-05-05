#ifndef PEMINJAM_H
#define PEMINJAM_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buku.h"

typedef enum {
    DOSEN = 1,
    MHS = 2,
    UMUM = 3
} Prioritas;

typedef struct Peminjam {
    char nama[50];
    Prioritas prioritas;
    struct Peminjam* nextPeminjam;
    struct Buku* nextBuku; // untuk menandakan ujung
} Peminjam;

// Queue operations
Peminjam* createPeminjam(const char nama[], Prioritas pr);
void clearPeminjam(Peminjam *head);

#endif // PEMINJAM_H