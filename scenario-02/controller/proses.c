#include "proses.h"

PeminjamanAktif *PeminjamanList = NULL;

// method initalize antrean
void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr)
{
    if (!buku)
        return;

    Peminjam *nodePeminjamBaru = createPeminjam(nama, pr);
    if (!nodePeminjamBaru)
    {
        printf("gagal alokasi peminjam\n");
        return;
    }

    Peminjam *curr = buku->antrean;
    Peminjam *prev = NULL;

    //                        dosen < mhs < umum
    while (curr != NULL && curr->prioritas <= pr)
    {
        prev = curr;
        curr = curr->next;
        if (curr != NULL && curr->next != NULL && curr->next->prioritas > pr)
        {
            prev = curr;
            curr = curr->next;
            break; // jika ada peminjam dengan prioritas yang sama, masukkan di belakang
        }
    }

    nodePeminjamBaru->next = curr; // jika awal antrean atau ujung, curr == NULL

    if (prev == NULL)
    {
        buku->antrean = nodePeminjamBaru;
    }
    else
    {
        prev->next = nodePeminjamBaru;
    }
}

// method execute peminjaman
void prosesPeminjaman(Buku *buku)
{
    if (!buku)
        return;
    if (buku->antrean == NULL)
    {
        printf("Antrean di buku \"%s\" kosong.\n", buku->judul);
        return;
    }

    if (buku->stock <= 0)
    {
        printf("Stock buku \"%s\" habis.\n", buku->judul);
        return;
    }

    Peminjam *peminjam = buku->antrean;
    buku->antrean = peminjam->next;
    buku->stock--;

    PeminjamanAktif *baru = malloc(sizeof(PeminjamanAktif));
    if (!baru)
    {
        printf("Gagal alokasi memori untuk peminjaman aktif\n");
        buku->antrean = peminjam;
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

    Peminjam *curr = buku->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && strcmp(curr->nama, nama) != 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("Peminjam \"%s\" tidak ditemukan dalam antrean buku \"%s\".\n",
               nama, buku->judul);
        return;
    }

    if (prev == NULL) // jika yang dihapus adalah pertama
    {
        buku->antrean = curr->next;
    }
    else
    {
        prev->next = curr->next;
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