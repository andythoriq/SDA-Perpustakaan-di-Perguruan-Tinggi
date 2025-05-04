// buku.c

#include "buku.h"

#define MAX_BUKU 100

Buku daftarBuku[MAX_BUKU];
int jumlahBuku = 0;

void initList()
{
    jumlahBuku = 0;
}

int isListEmpty()
{
    return jumlahBuku == 0;
}

Buku *createBuku(char judul[], int stock)
{
    Buku *b = (Buku *)malloc(sizeof(Buku));
    if (b == NULL)
    {
        printf("Gagal alokasi Buku\n");
        return NULL;
    }
    strcpy(b->judul, judul);
    b->stock = stock;
    b->antrean = NULL;
    return b;
}

void insertBuku(char judul[], int stock)
{
    if (jumlahBuku >= MAX_BUKU)
    {
        printf("Database buku penuh!\n");
        return;
    }
    strcpy(daftarBuku[jumlahBuku].judul, judul);
    daftarBuku[jumlahBuku].stock = stock;
    daftarBuku[jumlahBuku].antrean = NULL;
    jumlahBuku++;
}

void deleteBuku(char judul[])
{
    int index = -1;
    for (int i = 0; i < jumlahBuku; i++)
    {
        if (strcmp(daftarBuku[i].judul, judul) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Buku \"%s\" tidak ditemukan!\n", judul);
        return;
    }
    // clear antrean sebelum hapus buku
    clearPeminjam(daftarBuku[index].antrean);

    for (int i = index; i < jumlahBuku - 1; i++)
    {
        daftarBuku[i] = daftarBuku[i + 1];
    }
    jumlahBuku--;
}

Buku *findBuku(char judul[])
{
    for (int i = 0; i < jumlahBuku; i++)
    {
        if (strcmp(daftarBuku[i].judul, judul) == 0)
        {
            return &daftarBuku[i];
        }
    }
    return NULL;
}

void displayAllBuku()
{
    if (isListEmpty())
    {
        printf("List Buku kosong!\n");
        return;
    }
    printf("Daftar Buku:\n");
    for (int i = 0; i < jumlahBuku; i++)
    {
        printf("%d. %s (Stock: %d)\n", i + 1, daftarBuku[i].judul, daftarBuku[i].stock);
    }
}

void clearListBuku()
{
    for (int i = 0; i < jumlahBuku; i++)
    {
        clearPeminjam(daftarBuku[i].antrean);
    }
    jumlahBuku = 0;
}
