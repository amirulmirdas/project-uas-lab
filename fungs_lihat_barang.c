#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "tambah_barang.txt"

void lihat_daftar_barang()
{
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    char nama[50];
    int jumlah;
    float harga;

    printf("Daftar Barang:\n");
    while (fscanf(fp, "%s %d %f", nama, &jumlah, &harga) == 3)
    {
        printf("Nama Barang: %s\n", nama);
        printf("Jumlah Barang: %d\n", jumlah);
        printf("Harga Barang: %.2f\n", harga);
    }
    fclose(fp);
}