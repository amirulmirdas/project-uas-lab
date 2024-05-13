#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BARANG 100
#define FILENAME "data_barang.txt"
#define USER_FILENAME "data_user.txt"

struct Barang
{
    char nama[50];
    int jumlah;
    float harga;
};

struct User
{
    char username[50];
    char password[50];
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
        printf("------------------------\n");
    }

    fclose(fp);
}

void pembayaran()
{
    if (jumlah_barang > 0)
    {
        float total_harga = 0;
        for (int i = 0; i < jumlah_barang; i++)
        {
            total_harga += toko[i].jumlah * toko[i].harga;
        }

        printf("Total Harga: %.2f\n", total_harga);

        float jumlah_uang;
        printf("Jumlah Uang: ");
        scanf("%f", &jumlah_uang);

        if (jumlah_uang >= total_harga)
        {
            float kembalian = jumlah_uang - total_harga;
            printf("Kembalian: %.2f\n", kembalian);
        }
        else
        {
            printf("Maaf, uang tidak mencukupi.\n");
        }
    }
    else
    {
        printf("Toko kosong.\n");
    }
}

int login()
{
    char username[50];
    char password[50];
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(USER_FILENAME, "r");
    if (fp == NULL)
    {
        printf("Gagal membuka file.\n");
        return 0; // Login gagal
    }

    struct User user;
    while (fscanf(fp, "%s %s", user.username, user.password) == 2)
    {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0)
        {
            fclose(fp);
            return 1; // Login berhasil
        }
    }

    fclose(fp);
    return 0; // Login gagal
}

void register_user()
{
    char username[50];
    char password[50];
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(USER_FILENAME, "a");
    if (fp == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);

    printf("Registrasi berhasil.\n");
}

int main()
{
    printf("Selamat datang!\n");
    printf("1. Login\n");
    printf("2. Registrasi\n");
    printf("Pilihan: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        int logged_in = login();

        if (logged_in)
        {
            printf("Login berhasil!\n");

            FILE *fp = fopen(FILENAME, "r");
            if (fp == NULL)
            {
                printf("Gagal membuka file.\n");
                return 1;
            }

            char nama[50];
            int jumlah;
            float harga;

            while (fscanf(fp, "%s %d %f", nama, &jumlah, &harga) == 3)
            {
                struct Barang new_barang;
                strcpy(new_barang.nama, nama);
                new_barang.jumlah = jumlah;
                new_barang.harga = harga;
                toko[jumlah_barang] = new_barang;
                jumlah_barang++;
            }

            fclose(fp);

            int pilihan;
            while (1)
            {
                printf("\nMenu:\n");
                printf("1. Tambah Brang\n");
                printf("2. Kurangi Barang\n");
                printf("3. Lihat Daftar Barang\n");
                printf("4. Pembayaran\n");
                printf("5. Keluar\n");
                printf("Pilihan: ");
                scanf("%d", &pilihan);

                switch (pilihan)
                {
                case 1:
                    tambah_barang();
                    break;
                case 2:
                    kurangi_barang();
                    break;
                case 3:
                    lihat_daftar_barang();
                    break;
                case 4:
                    pembayaran();
                    break;
                case 5:
                    printf("Terima kasih, sampai jumpa!\n");
                    return 0;
                default:
                    printf("Pilihan tidak valid.\n");
                    break;
                }
            }
        }
        else
        {
            printf("Login gagal. Aplikasi berhenti.\n");
        }
        break;
    }
    case 2:
        register_user();
        break;
    default:
        printf("Pilihan tidak valid.\n");
        break;
    }

    return 0;
}