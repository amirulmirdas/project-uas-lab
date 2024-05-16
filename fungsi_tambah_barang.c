#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BARANG 100
#define FILENAME "tambah_barang.txt"

struct Barang
{
    char nama[50];
    int jumlah;
    float harga;
};

struct Barang toko[MAX_BARANG];
int jumlah_barang = 0;

void tambah_barang()
{
    if (jumlah_barang < MAX_BARANG)
    {
        struct Barang new_barang;

        printf("Nama Barang: ");
        scanf("%s", new_barang.nama);

        printf("Jumlah Barang: ");
        scanf("%d", &new_barang.jumlah);

        printf("Harga Barang: ");
        scanf("%f", &new_barang.harga);

        FILE *fp = fopen(FILENAME, "a");
        if (fp == NULL)
        {
            printf("Gagal membuka file.\n");
            return;
        }
        fprintf(fp, "%s %d %.2f\n", new_barang.nama, new_barang.jumlah, new_barang.harga);
        fclose(fp);

        toko[jumlah_barang] = new_barang;
        jumlah_barang++;

        printf("Barang berhasil ditambahkan.\n");
    }
    else
    {
        printf("Maaf, toko sudah penuh.\n");
    }
}