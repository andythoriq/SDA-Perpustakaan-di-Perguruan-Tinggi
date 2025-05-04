#ifndef LIST_ANTREAN_H
#define LIST_ANTREAN_H

#include "peminjam.h"
#include "buku.h"

typedef struct listAntrean {
    int indexBuku;
    struct Peminjam *antrean;
    struct listAntrean *next;
} listAntrean;

extern listAntrean *HEAD_ListAntrean;

int isListAntreanEmpty();
void insertListAntrean(listAntrean *newList);
listAntrean *getListAntreanByBuku(Buku *buku);
listAntrean *getListAntreanByBukuNull(Buku *buku);
listAntrean *createListAntrean();
void clearListAntrean();
#endif // LIST_ANTREAN_H