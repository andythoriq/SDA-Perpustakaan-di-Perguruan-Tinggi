#include "listantrean.h"

listAntrean *HEAD_ListAntrean = NULL;

int isListAntreanEmpty()
{
    return HEAD_ListAntrean == NULL;
}

listAntrean *createListAntrean()
{
    listAntrean *newList = (listAntrean *)malloc(sizeof(listAntrean));
    if (!newList)
    {
        printf("Gagal alokasi memori listAntrean\n");
        return NULL;
    }
    newList->indexBuku = -1;
    newList->antrean = NULL;
    newList->next = NULL;
    return newList;
}

void insertListAntrean(listAntrean *newList)
{
    if (!newList)
        return;
    newList->next = HEAD_ListAntrean;
    HEAD_ListAntrean = newList;
}

listAntrean *getListAntreanByBuku(Buku *buku)
{
    if (!buku)
        return NULL;

    int indexBuku = buku - daftarBuku;

    listAntrean *current = HEAD_ListAntrean;
    while (current != NULL)
    {
        if (current->indexBuku == indexBuku)
        {
            return current;
        }
        current = current->next;
    }

    // Kalau tidak ketemu, buat baru
    listAntrean *newList = createListAntrean();
    if (newList == NULL)
        return NULL;
    newList->indexBuku = indexBuku;
    insertListAntrean(newList);
    return newList;
}

listAntrean *getListAntreanByBukuNull(Buku *buku)
{
    if (!buku)
        return NULL;

    int indexBuku = buku - daftarBuku;

    listAntrean *current = HEAD_ListAntrean;
    while (current != NULL)
    {
        if (current->indexBuku == indexBuku)
        {
            return current;
        }
        current = current->next;
    }

    return NULL; // Tidak ditemukan
}

void clearListAntrean()
{
    listAntrean *current = HEAD_ListAntrean;
    while (current != NULL)
    {
        listAntrean *next = current->next;
        clearPeminjam(current->antrean);
        free(current);
        current = next;
    }
    HEAD_ListAntrean = NULL;
}
