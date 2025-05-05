#ifndef LIST_ANTREAN_H
#define LIST_ANTREAN_H

#include "peminjam.h"

/*
    ujung antrean adalah buku
    jadi kondisi untuk menyatakan ujung antrean adalah
    listAntrean->antrean == Buku
 */

typedef struct listAntrean {
    struct Peminjam *antrean;
    // struct Buku *buku; // jika dibutuhkan
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