#include "proses.h"

PeminjamanAktif *PeminjamanList = NULL; 

void setUjungJadiBuku(listAntrean* listAntrean, Buku* buku) // kalau ujung adalah NULL
{
    Peminjam *curr = listAntrean->antrean;
    if (!curr)
        return;

    while (curr->nextPeminjam != NULL)
    {
        curr = curr->nextPeminjam; // stop sebelum NULL
    }
    curr->nextBuku = buku;
}

// method initalize antrean
void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr)
{
    if (!buku || !nama || nama[0] == '\0')
        return;

    listAntrean *listAntrean = getListAntreanByBuku(buku);

    Peminjam *peminjamBaru = createPeminjam(nama, pr);

    // jika antrean kosong
    if (listAntrean->antrean == NULL)
    {
        peminjamBaru->nextBuku = buku;
        listAntrean->antrean = peminjamBaru;
        return;
    }

    Peminjam *curr = listAntrean->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && curr->prioritas <= pr)
    {
        prev = curr;
        curr = curr->nextPeminjam;
        if (curr->nextBuku == buku) { // jika sudah di ujung
            prev = curr;
            curr->nextBuku = NULL; // jadiin null dulu supaya nanti dipakai oleh node yang paling ujung
            curr = NULL;
        }
    }

    peminjamBaru->nextPeminjam = curr;

    if (prev == NULL) // awal
    {
        listAntrean->antrean = peminjamBaru;
    }
    else // tengah - ujung
    {
        prev->nextPeminjam = peminjamBaru;
    }

    setUjungJadiBuku(listAntrean, buku);
}

// method execute peminjaman
void prosesPeminjaman(Buku *buku)
{
    if (!buku)
        return;

    listAntrean *listAntrean = getListAntreanByBukuNull(buku); //return null kalau kosong
    if (listAntrean == NULL || listAntrean->antrean == NULL)
    {
        printf("Tidak ada antrean peminjaman untuk buku ini!\n");
        return;
    }

    if (buku->stock <= 0)
    {
        printf("Stock buku \"%s\" habis.\n", buku->judul);
        return;
    }

    Peminjam *peminjam = listAntrean->antrean; // peminjam yang akan diproses
    Peminjam *nextPeminjam = peminjam->nextPeminjam;

    listAntrean->antrean = nextPeminjam;
    peminjam->nextPeminjam = NULL;

    buku->stock--;

    PeminjamanAktif *baru = malloc(sizeof(PeminjamanAktif));
    if (!baru)
    {
        printf("Gagal alokasi memori untuk peminjaman aktif\n");

        peminjam->nextPeminjam = nextPeminjam;
        listAntrean->antrean = peminjam;
        buku->stock++;
        return;
    }

    baru->buku = buku;
    baru->peminjam = peminjam;
    baru->next = PeminjamanList;
    PeminjamanList = baru;

    printf("Memproses peminjaman \"%s\" (prioritas %d) untuk buku \"%s\".\n",
           peminjam->nama, peminjam->prioritas, buku->judul);
}

void prosesPengembalian(Buku *buku, const char nama[])
{
    if (!buku || !nama || nama[0] == '\0')
        return;

    PeminjamanAktif *curr = PeminjamanList;
    PeminjamanAktif *prev = NULL;

    while (curr != NULL &&
           !(strcmp(curr->peminjam->nama, nama) == 0 && curr->buku == buku))
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("Peminjaman aktif untuk \"%s\" pada buku \"%s\" tidak ditemukan.\n",
               nama, buku->judul);
        return;
    }

    if (prev == NULL) // jika yang dihapus adalah pertama
    {
        PeminjamanList = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    buku->stock++;

    printf("Mengembalikan \"%s\" yang dipinjam oleh \"%s\".\n",
           curr->buku->judul, curr->peminjam->nama);

    free(curr->peminjam);
    free(curr);
}

void batalkanAntrean(Buku *buku, const char nama[])
{
    if (!buku || !nama || nama[0] == '\0')
        return;

    listAntrean *listAntrean = getListAntreanByBukuNull(buku);
    if (listAntrean == NULL || listAntrean->antrean == NULL) { // return null kalau kosong
        printf("List kosong!");
        return;
    }
    Peminjam *curr = listAntrean->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && strcmp(curr->nama, nama) != 0)
    {
        prev = curr;
        curr = curr->nextPeminjam;
    }

    if (curr == NULL) {
        printf("Peminjam \"%s\" tidak ditemukan dalam antrean buku \"%s\".\n",
               nama, buku->judul);
        return;
    }

    if (prev == NULL) // jika yang dihapus adalah pertama
    {
        listAntrean->antrean = curr->nextPeminjam;
    }
    else
    {
        prev->nextPeminjam = curr->nextPeminjam;
    }

    free(curr);
    printf("Antrean peminjam \"%s\" untuk buku \"%s\" dibatalkan.\n",
           nama, buku->judul);
}

void lihatPeminjamanAktif()
{
    if (PeminjamanList == NULL)
    {
        printf("Tidak ada peminjaman aktif.\n");
        return;
    }

    printf("Daftar Peminjaman Aktif:\n");
    PeminjamanAktif *curr = PeminjamanList;
    while (curr != NULL)
    {
        printf("- %s (prioritas %d) untuk buku \"%s\"\n",
               curr->peminjam->nama, curr->peminjam->prioritas, curr->buku->judul);
        curr = curr->next;
    }
}

void clearPeminjamanAktif()
{
    PeminjamanAktif *curr = PeminjamanList;
    while (curr != NULL)
    {
        PeminjamanAktif *temp = curr;
        curr = curr->next;
        free(temp->peminjam);
        free(temp);
    }
    PeminjamanList = NULL;
}

void displayAllBukuAndAntrean()
{
    if (isListBukuEmpty())
    {
        printf("List Buku kosong!\n");
        return;
    }

    Buku *currentBuku = HEAD_Buku;
    while (currentBuku != NULL)
    {
        printf("\nBuku: %s\nStock: %d\n", currentBuku->judul, currentBuku->stock);
        printf("------------------------\n");

        listAntrean* current = getListAntreanByBukuNull(currentBuku);
        if (current != NULL && current->antrean != NULL)
        {
            Peminjam *currentPeminjam = current->antrean;
            while (currentPeminjam != NULL)
            {
                printf("Nama: %s, Prioritas: %d (%s)\n", 
                    currentPeminjam->nama, 
                    currentPeminjam->prioritas,
                    currentPeminjam->prioritas == 1 ? "Dosen" : 
                    currentPeminjam->prioritas == 2 ? "Mahasiswa" : "Umum"
                );
                currentPeminjam = currentPeminjam->nextPeminjam;
            }
        } else {
            printf("belum ada yang meminjam buku ini\n");
        }
        printf("------------------------\n");
        currentBuku = currentBuku->next;
    }
}