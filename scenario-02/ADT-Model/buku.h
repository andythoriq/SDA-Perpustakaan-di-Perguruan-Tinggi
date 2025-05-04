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
    struct Buku* next;
} Buku;

// Linked list operations
extern Buku* HEAD;
void initList();
int isListEmpty();
Buku* createBuku(char judul[], int stock);
void insertBuku(char judul[], int stock);
void deleteBuku(char judul[]);
Buku* findBuku(char judul[]);
void displayAllBuku();
void clearList();

#endif // BUKU_H