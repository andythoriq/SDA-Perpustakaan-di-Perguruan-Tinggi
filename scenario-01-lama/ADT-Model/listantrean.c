#include "listantrean.h"

listAntrean *HEAD_ListAntrean = NULL;

int isListAntreanEmpty()
{
    return HEAD_ListAntrean == NULL;
}

listAntrean *createListAntrean()
{
    listAntrean *newList = (listAntrean *)malloc(sizeof(listAntrean));
    if (newList == NULL)
    {
        printf("Gagal alokasi memori listAntrean\n");
        return NULL;
    }

    newList->buku = NULL;
    newList->antrean = NULL;
    newList->next = NULL;
    return newList;
}

void insertListAntrean(listAntrean *newList)
{
    if (newList == NULL)
        return;

    newList->next = HEAD_ListAntrean;
    HEAD_ListAntrean = newList;
}

listAntrean *getListAntreanByBuku(Buku *buku)
{
    if (buku == NULL)
        return NULL;

    listAntrean *current = HEAD_ListAntrean;
    while (current != NULL)
    {
        if (current->buku == buku)
        {
            return current;
        }
        current = current->next;
    }

    // Jika tidak ketemu, buat baru
    listAntrean *newList = createListAntrean();
    if (newList == NULL)
    {
        return NULL;
    }
    newList->buku = buku;
    insertListAntrean(newList);
    return newList;
}

listAntrean *getListAntreanByBukuNull(Buku *buku)
{
    if (buku == NULL)
        return NULL;

    listAntrean *current = HEAD_ListAntrean;
    while (current != NULL)
    {
        if (current->buku == buku)
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
        Peminjam *curr = current->antrean;
        while (curr != NULL)
        {
            Peminjam *temp = curr;
            curr = curr->next;
            free(temp);
        }
        free(current);
        current = next;
    }
    HEAD_ListAntrean = NULL;
}
