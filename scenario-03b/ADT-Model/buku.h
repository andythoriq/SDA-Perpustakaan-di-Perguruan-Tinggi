#ifndef BUKU_H
#define BUKU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peminjam.h"

typedef struct Buku
{
    char judul[50];
    int stock;
} Buku;

#define MAX_BUKU 100

extern Buku daftarBuku[MAX_BUKU];
extern int jumlahBuku;

void initList();
int isListEmpty();

void insertBuku(char judul[], int stock);
void deleteBuku(char judul[]);
Buku *findBuku(char judul[]);

#endif // BUKU_H