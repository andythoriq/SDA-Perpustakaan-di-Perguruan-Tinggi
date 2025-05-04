#include "buku.h"

Buku* HEAD = NULL;

void initList() {
    HEAD = NULL;
}

int isListEmpty() {
    return HEAD == NULL;
}

int isBukuExist(char judul[]) {
    Buku* current = HEAD;
    while (current != NULL) {
        if (strcmp(current->judul, judul) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Buku* createBuku(char judul[], int stock) {
    Buku* newBuku = (Buku*)malloc(sizeof(Buku));
    strcpy(newBuku->judul, judul);
    newBuku->stock = stock;
    newBuku->antrean = NULL;
    newBuku->next = NULL;
    return newBuku;
}

void insertBuku(char judul[], int stock) {
    if (isBukuExist(judul)) {
        printf("Buku dengan judul \"%s\" sudah ada!\n", judul);
        return;
    }

    Buku* newBuku = createBuku(judul, stock);
    
    if (isListEmpty()) {
        HEAD = newBuku;
    } else {
        newBuku->next = HEAD;
        HEAD = newBuku;
    }
}

void deleteBuku(char judul[]) {
    if (isListEmpty()) {
        printf("List is empty!\n");
        return;
    }

    Buku* current = HEAD;
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
        HEAD = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}

Buku* findBuku(char judul[]) {
    Buku* current = HEAD;
    while (current != NULL) {
        if (strcmp(current->judul, judul) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void displayAllBuku() {
    if (isListEmpty()) {
        printf("List is empty!\n");
        return;
    }

    Buku* current = HEAD;
    while (current != NULL) {
        printf("\nBuku: %s\nStock: %d\n", current->judul, current->stock);
        
        if (current->antrean != NULL) {
            printf("Daftar Antrean:\n");
            Peminjam* peminjam = current->antrean;
            while (peminjam != NULL) {
                printf("- %s (", peminjam->nama);
                switch(peminjam->prioritas) {
                    case DOSEN: printf("DOSEN"); break;
                    case MHS: printf("MAHASISWA"); break;
                    case UMUM: printf("UMUM"); break;
                }
                printf(")\n");
                peminjam = peminjam->next;
            }
        } else {
            printf("Tidak ada antrean\n");
        }
        printf("------------------------\n");
        current = current->next;
    }
}

void clearList()
{
    while (!isListEmpty())
    {
        Buku *current = HEAD;
        clearPeminjam(current->antrean);
        deleteBuku(HEAD->judul);
    }
}
