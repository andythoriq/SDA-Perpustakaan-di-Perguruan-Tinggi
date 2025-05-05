#include "buku.h"

Buku* HEAD_Buku = NULL;

void initList() {
    HEAD_Buku = NULL;
}

int isListBukuEmpty() {
    return HEAD_Buku == NULL;
}

int isBukuExist(char judul[])
{
    Buku *current = HEAD_Buku;
    while (current != NULL)
    {
        if (strcmp(current->judul, judul) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Buku* createBuku(char judul[], int stock) {
    Buku* newBuku = (Buku*)malloc(sizeof(Buku));
    if (newBuku == NULL) {
        printf("Alokasi gagal");
        return NULL;
    }
    strcpy(newBuku->judul, judul);
    newBuku->stock = stock;
    newBuku->next = NULL;
    return newBuku;
}

void insertBuku(char judul[], int stock) {
    if (isBukuExist(judul)) {
        printf("Buku dengan judul \"%s\" sudah ada!\n", judul);
        return;
    }
    Buku* newBuku = createBuku(judul, stock);
    
    if (isListBukuEmpty()) {
        HEAD_Buku = newBuku;
    } else {
        newBuku->next = HEAD_Buku;
        HEAD_Buku = newBuku;
    }
}

void deleteBuku(char judul[]) {
    if (isListBukuEmpty()) {
        printf("List is empty!\n");
        return;
    }

    Buku* current = HEAD_Buku;
    Buku* prev = NULL;

    while (current != NULL && strcmp(current->judul, judul) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Buku not found!\n");
        return;
    }

    if (prev == NULL) {
        HEAD_Buku = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}

Buku* findBuku(char judul[]) {
    Buku* current = HEAD_Buku;
    while (current != NULL) {
        if (strcmp(current->judul, judul) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void clearListBuku()
{
    while (!isListBukuEmpty())
    {
        Buku *current = HEAD_Buku;
        deleteBuku(HEAD_Buku->judul);
    }
}
