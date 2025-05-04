#ifndef PROSES_H
#define PROSES_H

#include "../ADT-Model/buku.h"

typedef struct PeminjamanAktif {
    Buku *buku;
    Peminjam *peminjam;
    struct PeminjamanAktif *next;
} PeminjamanAktif;

extern PeminjamanAktif *PeminjamanList;

void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr);
void prosesPeminjaman(Buku *buku);
void prosesPengembalian(Buku *buku, const char nama[]);
void batalkanAntrean(Buku *buku, const char nama[]);
void lihatPeminjamanAktif();
void clearPeminjamanAktif();

#endif // PROSES_H