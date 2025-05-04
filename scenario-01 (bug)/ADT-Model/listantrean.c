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

    newList->antrean = NULL;
    newList->next = NULL;
    return newList;
}

void insertListAntrean(listAntrean *newList)
{
    if (newList == NULL)
        return;

    if (isListAntreanEmpty())
    {
        HEAD_ListAntrean = newList;
    }
    else
    {
        newList->next = HEAD_ListAntrean;
        HEAD_ListAntrean = newList;
    }
}

listAntrean *getListAntreanByBuku(Buku *buku)
{
    // if HEAD kosong -> buat list baru
    if (HEAD_ListAntrean == NULL)
    {
        listAntrean *newList = createListAntrean();
        if (newList == NULL)
        {
            return NULL;
        }
        insertListAntrean(newList);
        return newList;
    }

    listAntrean *current = HEAD_ListAntrean;

    while (current != NULL)
    {
        if (current->antrean != NULL)
        {
            Peminjam *curr = current->antrean;
            while (curr != NULL)
            {
                // jika menemukan antrean yang terhubung dengan buku ini
                if ((void *)curr->next == (void *)buku)
                {
                    return current;
                }
                curr = (Peminjam *)curr->next;
            }
        }
        current = current->next;
    }

    // jika tidak ketemu, berarti buat listAntrean baru
    listAntrean *newList = createListAntrean();
    if (newList == NULL)
    {
        return NULL;
    }
    insertListAntrean(newList);
    return newList;
}

listAntrean *getListAntreanByBukuNull(Buku *buku)
{
    if (HEAD_ListAntrean == NULL || buku == NULL)
    {
        return NULL;
    }

    listAntrean *current = HEAD_ListAntrean;

    while (current != NULL)
    {
        if (current->antrean != NULL)
        {
            Peminjam *curr = current->antrean;
            while (curr != NULL)
            {
                // kalau menemukan antrean yang terhubung dengan buku ini
                if ((void *)curr->next == (void *)buku)
                {
                    return current;
                }
                curr = (Peminjam *)curr->next;
            }
        }
        current = current->next;
    }

    // jika tidak ketemu=
    return NULL;
}

void clearListAntrean()
{
    listAntrean *current = HEAD_ListAntrean;
    while (current != NULL)
    {
        listAntrean *next = current->next;
        if (current->antrean != NULL)
        {
            Peminjam *curr = current->antrean;
            while (curr != NULL && (void*)curr->next != (void*)current)
            // while (curr != NULL && curr->next != current)
            {
                Peminjam *temp = curr;
                curr = (Peminjam*) curr->next;
                free(temp);
            }
        }
        free(current);
        current = next;
    }
    HEAD_ListAntrean = NULL;
}