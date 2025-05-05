#ifndef PROSES_H
#define PROSES_H

#include "../ADT-Model/listantrean.h"

typedef struct PeminjamanAktif {
    Buku *buku;
    Peminjam *peminjam;
    struct PeminjamanAktif *next;
} PeminjamanAktif;

extern PeminjamanAktif *PeminjamanList;

void setUjungJadiBuku(listAntrean *listAntrean, Buku *buku);

void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr);
void prosesPeminjaman(Buku *buku);
void prosesPengembalian(Buku *buku, const char nama[]);
void batalkanAntrean(Buku *buku, const char nama[]);
void lihatPeminjamanAktif();
void clearPeminjamanAktif();
void displayAllBukuAndAntrean();

#endif // PROSES_H