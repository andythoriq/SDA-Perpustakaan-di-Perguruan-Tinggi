#include "proses.h"

PeminjamanAktif *PeminjamanList = NULL;

void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr)
{
    if (!buku || !nama || nama[0] == '\0')
        return;

    listAntrean *list = getListAntreanByBuku(buku);
    if (list == NULL)
        return;

    Peminjam *baru = createPeminjam(nama, pr);

    if (list->antrean == NULL)
    {
        list->antrean = baru;
        return;
    }

    Peminjam *curr = list->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && curr->prioritas <= pr)
    {
        prev = curr;
        curr = curr->next;
    }

    baru->next = curr;
    if (prev == NULL)
        list->antrean = baru;
    else
        prev->next = baru;
}

void prosesPeminjaman(Buku *buku)
{
    if (!buku)
        return;

    listAntrean *list = getListAntreanByBukuNull(buku);
    if (list == NULL || list->antrean == NULL)
    {
        printf("Tidak ada antrean peminjaman untuk buku ini!\n");
        return;
    }

    if (buku->stock <= 0)
    {
        printf("Stock buku \"%s\" habis.\n", buku->judul);
        return;
    }

    Peminjam *peminjam = list->antrean;
    list->antrean = peminjam->next;

    buku->stock--;

    PeminjamanAktif *baru = malloc(sizeof(PeminjamanAktif));
    if (!baru)
    {
        printf("Gagal alokasi memori untuk peminjaman aktif\n");
        peminjam->next = list->antrean;
        list->antrean = peminjam;
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

    while (curr != NULL && !(strcmp(curr->peminjam->nama, nama) == 0 && curr->buku == buku))
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("Peminjaman aktif untuk \"%s\" pada buku \"%s\" tidak ditemukan.\n", nama, buku->judul);
        return;
    }

    if (prev == NULL)
        PeminjamanList = curr->next;
    else
        prev->next = curr->next;

    buku->stock++;

    printf("Mengembalikan \"%s\" yang dipinjam oleh \"%s\".\n", curr->buku->judul, curr->peminjam->nama);

    free(curr->peminjam);
    free(curr);
}

void batalkanAntrean(Buku *buku, const char nama[])
{
    if (!buku || !nama || nama[0] == '\0')
        return;

    listAntrean *list = getListAntreanByBukuNull(buku);
    if (list == NULL || list->antrean == NULL)
    {
        printf("List kosong!\n");
        return;
    }

    Peminjam *curr = list->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && strcmp(curr->nama, nama) != 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("Peminjam \"%s\" tidak ditemukan dalam antrean buku \"%s\".\n", nama, buku->judul);
        return;
    }

    if (prev == NULL)
        list->antrean = curr->next;
    else
        prev->next = curr->next;

    free(curr);

    printf("Antrean peminjam \"%s\" untuk buku \"%s\" dibatalkan.\n", nama, buku->judul);
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

        listAntrean *current = getListAntreanByBukuNull(currentBuku);
        if (current != NULL && current->antrean != NULL)
        {
            Peminjam *currentPeminjam = current->antrean;
            while (currentPeminjam != NULL)
            {
                printf("Nama: %s, Prioritas: %d (%s)\n",
                       currentPeminjam->nama,
                       currentPeminjam->prioritas,
                       currentPeminjam->prioritas == 1 ? "Dosen" : currentPeminjam->prioritas == 2 ? "Mahasiswa"
                                                                                                   : "Umum");
                currentPeminjam = currentPeminjam->next;
            }
        }
        else
        {
            printf("belum ada yang meminjam buku ini\n");
        }
        printf("------------------------\n");
        currentBuku = currentBuku->next;
    }
}
