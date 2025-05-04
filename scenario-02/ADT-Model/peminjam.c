#include "peminjam.h"

Peminjam* createPeminjam(const char nama[], Prioritas pr) {
    if (!nama || nama[0] == '\0') {
        return NULL;
    }
    if (pr < DOSEN || pr > UMUM) {
        return NULL;
    }

    Peminjam* p = malloc(sizeof(Peminjam));
    if (p) {
        strncpy(p->nama, nama, sizeof(p->nama) - 1);
        p->nama[sizeof(p->nama) - 1] = '\0';
        p->prioritas = pr;
        p->next = NULL;
    }
    return p;
}

void clearPeminjam(Peminjam *head)
{
    while (head != NULL)
    {
        Peminjam *temp = head;
        head = head->next;
        free(temp);
    }
}