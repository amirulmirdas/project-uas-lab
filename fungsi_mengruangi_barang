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


void kurangi_barang()
{
    if (jumlah_barang > 0)
    {
        char nama_barang[50];
        printf("Nama Barang: ");
        scanf("%s", nama_barang);

        int i, found = 0;
        for (i = 0; i < jumlah_barang; i++)
        {
            if (strcmp(toko[i].nama, nama_barang) == 0)
            {
                int jumlah_kurang;
                printf("Jumlah Kurang Barang: ");
                scanf("%d", &jumlah_kurang);

                if (jumlah_kurang <= toko[i].jumlah)
                {
                    toko[i].jumlah -= jumlah_kurang;

                    FILE *fp = fopen(FILENAME, "a");
                    if (fp == NULL)
                    {
                        printf("Gagal membuka file.\n");
                        return;
                    }
                    fprintf(fp, "%s %d %.2f\n", toko[i].nama, toko[i].jumlah, toko[i].harga);
                    fclose(fp);

                    printf("Barang berhasil dikurangi.\n");
                }
                else
                {
                    printf("Maaf, stok barang tidak mencukupi.\n");
                }

                found = 1;
                break;
            }
        }

        if (!found)
        {
            printf("Barang tidak ditemukan.\n");
        }
    }
    else
    {
        printf("Toko kosong.\n");
    }
}
