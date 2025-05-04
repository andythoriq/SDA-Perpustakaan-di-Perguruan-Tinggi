#include "menu.h"

void displayMenu() {
    printf("\n PERPUSTAKAAN:\n");
    printf("1. Insert Buku\n");
    printf("2. Display Buku\n");
    printf("3. Daftar yang Akan Meminjam\n");
    printf("4. Proses Pinjaman\n");
    printf("5. Batalkan Pinjaman\n");
    printf("6. Proses Pengembalian\n");
    printf("7. Lihat yang Sedang Meminjam\n");
    printf("0. Keluar\n");
}

int getPilihan() {
    int pilihan;
    printf("Pilihan Anda: ");
    scanf("%d", &pilihan);
    getchar();
    return pilihan;
}

void inputString(char *buffer, size_t size, const char *prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

int inputInt(const char *prompt) {
    int value;
    printf("%s", prompt);
    scanf("%d", &value);
    getchar();
    return value;
}