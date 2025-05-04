#ifndef BUKU_H
#define BUKU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Buku {
    char judul[50];
    int stock;
    struct Buku* next;
    // void * next;
} Buku;

// Linked list operations
extern Buku* HEAD_Buku;
void initList();
int isListBukuEmpty();
Buku* createBuku(char judul[], int stock);
void insertBuku(char judul[], int stock);
void deleteBuku(char judul[]);
Buku* findBuku(char judul[]);
void clearListBuku();

#endif // BUKU_H