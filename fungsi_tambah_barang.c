#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mendefinisikan jumlah maksimum barang yang dapat disimpan
#define MAX_BARANG 100
// Nama file tempat menyimpan data barang
#define FILENAME "tambah_barang.txt"

// struct untuk menyimpan data barang
struct Barang
{
    char nama[50];
    int jumlah;
    float harga;
};

// Array untuk menyimpan daftar barang dan variabel untuk menghitung jumlah barang 
struct Barang toko[MAX_BARANG];
int jumlah_barang = 0;

// Fungsi untuk menambahkan barang baru
void tambah_barang()
{
    // Memeriksa apakah masih ada ruang untuk menambahkan barang baru
    if (jumlah_barang < MAX_BARANG)
    {
        struct Barang new_barang;
    // Meminta input user untuk nama barang
        printf("Nama Barang: ");
        scanf("%s", new_barang.nama);

    // Meminta input user untuk jumlah barang
        printf("Jumlah Barang: ");
        scanf("%d", &new_barang.jumlah);

    // Meminta input user untuk harga barang
        printf("Harga Barang: ");
        scanf("%f", &new_barang.harga);

    // Membuka file untuk menambahkan data barang baru
        FILE *fp = fopen(FILENAME, "a");
        if (fp == NULL)
        {
            printf("Gagal membuka file.\n");
            return;
        }
        // Menulis data barang baru ke file
        fprintf(fp, "%s %d %.2f\n", new_barang.nama, new_barang.jumlah, new_barang.harga);
        fclose(fp);

    // Menambahkan barang baru ke array toko dan mengupdate jumlah barang
        toko[jumlah_barang] = new_barang;
        jumlah_barang++;

        printf("Barang berhasil ditambahkan.\n");
    }
    else
    {
        //menampil pesan jika toko sudah penuh
        printf("Maaf, toko sudah penuh.\n");
    }
}
