#ifndef BUKU_H
#define BUKU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peminjam.h"

typedef struct Buku {
    char judul[50];
    int stock;
    Peminjam* antrean;
} Buku;

#define MAX_BUKU 100

extern Buku daftarBuku[MAX_BUKU];
extern int jumlahBuku;

void initList();
int isListEmpty();
Buku* createBuku(char judul[], int stock);
void insertBuku(char judul[], int stock);
void deleteBuku(char judul[]);
Buku* findBuku(char judul[]);
void displayAllBuku();
void clearListBuku();

#endif // BUKU_H