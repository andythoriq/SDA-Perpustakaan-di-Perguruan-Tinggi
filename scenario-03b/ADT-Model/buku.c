#include "buku.h"

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

void insertBuku(char judul[], int stock)
{
    if (jumlahBuku >= MAX_BUKU)
    {
        printf("list buku penuh!\n");
        return;
    }
    strcpy(daftarBuku[jumlahBuku].judul, judul);
    daftarBuku[jumlahBuku].stock = stock;
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
