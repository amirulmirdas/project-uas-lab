#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nama file tempat menyimpan data barang
#define FILENAME "tambah_barang.txt"

// Fungsi untuk melihat daftar barang dari file
void lihat_daftar_barang()
{
    // Membuka file dalam mode baca
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        // Jika file gagal dibuka, tampilkan pesan error dan keluar dari fungsi
        printf("Gagal membuka file.\n");
        return;
    }

    char nama[50];
    int jumlah;
    float harga;

    // Mencetak header untuk daftar barang
    printf("Daftar Barang:\n");
    // Membaca data dari file dan menampilkan informasi barang
    while (fscanf(fp, "%s %d %f", nama, &jumlah, &harga) == 3)
    {
        printf("Nama Barang: %s\n", nama);
        printf("Jumlah Barang: %d\n", jumlah);
        printf("Harga Barang: %.2f\n", harga);
    }
    fclose(fp); // Menutup file setelah selesai membaca
}
