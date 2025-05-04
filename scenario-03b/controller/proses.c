#include "proses.h"

PeminjamanAktif *PeminjamanList = NULL;

void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr)
{
    if (!buku || !nama || nama[0] == '\0')
        return;

    listAntrean *list = getListAntreanByBuku(buku);
    if (!list)
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
    if (!list || !list->antrean)
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

    PeminjamanAktif *baru = (PeminjamanAktif *)malloc(sizeof(PeminjamanAktif));
    if (!baru)
    {
        printf("Gagal alokasi peminjaman aktif\n");
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

    while (curr != NULL && !(curr->buku == buku && strcmp(curr->peminjam->nama, nama) == 0))
    {
        prev = curr;
        curr = curr->next;
    }

    if (!curr)
    {
        printf("Peminjaman tidak ditemukan.\n");
        return;
    }

    if (prev == NULL)
        PeminjamanList = curr->next;
    else
        prev->next = curr->next;

    buku->stock++;

    printf("Pengembalian \"%s\" yang dipinjam \"%s\".\n", buku->judul, curr->peminjam->nama);

    free(curr->peminjam);
    free(curr);
}

void batalkanAntrean(Buku *buku, const char nama[])
{
    if (!buku || !nama || nama[0] == '\0')
        return;

    listAntrean *list = getListAntreanByBukuNull(buku);
    if (!list || !list->antrean)
    {
        printf("Tidak ada antrean.\n");
        return;
    }

    Peminjam *curr = list->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && strcmp(curr->nama, nama) != 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (!curr)
    {
        printf("Peminjam \"%s\" tidak ditemukan dalam antrean.\n", nama);
        return;
    }

    if (prev == NULL)
        list->antrean = curr->next;
    else
        prev->next = curr->next;

    free(curr);

    printf("Antrean \"%s\" dibatalkan.\n", nama);
}

void lihatPeminjamanAktif()
{
    if (!PeminjamanList)
    {
        printf("Tidak ada peminjaman aktif.\n");
        return;
    }

    printf("Daftar Peminjaman Aktif:\n");
    PeminjamanAktif *curr = PeminjamanList;
    while (curr != NULL)
    {
        printf("- %s (Prioritas %d) meminjam \"%s\"\n",
               curr->peminjam->nama,
               curr->peminjam->prioritas,
               curr->buku->judul);
        curr = curr->next;
    }
}

void clearPeminjamanAktif()
{
    PeminjamanAktif *curr = PeminjamanList;
    while (curr)
    {
        PeminjamanAktif *next = curr->next;
        free(curr->peminjam);
        free(curr);
        curr = next;
    }
    PeminjamanList = NULL;
}

void displayAllBukuAndAntrean()
{
    if (isListEmpty())
    {
        printf("List Buku kosong!\n");
        return;
    }

    for (int i = 0; i < jumlahBuku; i++)
    {
        printf("\nBuku: %s\nStock: %d\n", daftarBuku[i].judul, daftarBuku[i].stock);
        printf("------------------------\n");

        listAntrean *list = getListAntreanByBukuNull(&daftarBuku[i]);
        if (list && list->antrean)
        {
            Peminjam *curr = list->antrean;
            while (curr)
            {
                printf("Nama: %s, Prioritas: %d (%s)\n",
                       curr->nama,
                       curr->prioritas,
                       curr->prioritas == 1 ? "Dosen" : curr->prioritas == 2 ? "Mahasiswa"
                                                                             : "Umum");
                curr = curr->next;
            }
        }
        else
        {
            printf("Belum ada yang meminjam buku ini\n");
        }
        printf("------------------------\n");
    }
}
