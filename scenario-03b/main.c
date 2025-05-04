#include "Utils/menu.h"
#include "controller/proses.h"

int main()
{
    char namaBuku[50], namaOrang[50];
    int pilihan = 0, stock, prioritas;

    do
    {
        displayMenu();
        pilihan = getPilihan();

        switch (pilihan)
        {
        case 1: // Insert Buku
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");
            stock = inputInt("Masukkan jumlah stock: ");
            insertBuku(namaBuku, stock);
            break;
        case 2: // Display Buku dan Antrean
            displayAllBukuAndAntrean();
            break;
        case 3: // Daftar yang Akan Meminjam
            inputString(namaOrang, sizeof(namaOrang), "Masukkan nama peminjam: ");
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");
            do {
                prioritas = inputInt("Pilih prioritas (1:DOSEN, 2:MAHASISWA, 3:UMUM): ");
                if (prioritas < DOSEN || prioritas > UMUM) {
                    printf("Prioritas tidak valid! Masukkan angka 1, 2, atau 3.\n");
                }
            } while (prioritas < DOSEN || prioritas > UMUM);
            
            Buku* bukuDipinjam = findBuku(namaBuku);
            if (bukuDipinjam != NULL) {
                initialAntreanPeminjaman(bukuDipinjam, namaOrang, prioritas);
                printf("Berhasil mendaftar antrian peminjaman\n");
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;
        case 4: // Proses Pinjaman
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");
            Buku* bukuProsesPinjam = findBuku(namaBuku);
            if (bukuProsesPinjam != NULL) {
                prosesPeminjaman(bukuProsesPinjam);
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;
        case 5: // Batalkan antrean
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");
            inputString(namaOrang, sizeof(namaOrang), "Masukkan nama peminjam: ");
            
            Buku* bukuBatalkan = findBuku(namaBuku);
            if (bukuBatalkan != NULL) {
                batalkanAntrean(bukuBatalkan, namaOrang);
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;
        case 6: // Proses Pengembalian
            inputString(namaOrang, sizeof(namaOrang), "Masukkan nama peminjam: ");
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");
            
            Buku* bukuDikembalikan = findBuku(namaBuku);
            if (bukuDikembalikan != NULL) {
                prosesPengembalian(bukuDikembalikan, namaOrang);
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;
        case 7: // Lihat yang Sedang Meminjam
            lihatPeminjamanAktif();
            break;
        case 0:
            printf("Keluar dari program.\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);

    clearListAntrean();
    clearPeminjamanAktif();
    return 0;
}
