#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // untuk menambahkan nanosleep

#define batas_barang 100              // Membuat batas maksimal barang yang bisa ditambahkan
#define FILENAME "data_barang.txt"    // Membuat file untuk menyimpan data barang
#define USER_FILENAME "data_user.txt" // Membuat file untuk menyimpan data user

struct Barang // Menggunakan struct untuk menggroping variabel dengan nama Barang
{
    char nama[50];
    int jumlah;
    float harga;
};

struct User // Menggunakan struct untuk menggroping variabel dengan nama User
{
    char username[50];
    char password[50];
};

struct Barang toko[batas_barang]; // Menggunakan struct dengan nama variabel toko dengan syarat max_barang yaitu 100
int jumlah_barang = 0;            // Mendeklarasikan jumlah barang dari 0

void printProgressBar(int progress, int total)
{ // membuat loading bar
    int barWidth = 50;
    printf("[");
    int pos = barWidth * progress / total;
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            printf("=");
        else if (i == pos)
            printf(">");
        else
            printf(" ");
    }
    printf("] %d%%\r", 100 * progress / total);
    fflush(stdout);
}

void tambah_barang() // Membuat fungsi tambah_barang
{
    if (jumlah_barang < batas_barang) // Jika jumlah barang kurang dari 100 maka kode akan berjalan
    {
        struct Barang new_barang;

        printf("Nama Barang: ");
        scanf("%s", new_barang.nama);

        printf("Jumlah Barang: ");
        scanf("%d", &new_barang.jumlah);

        printf("Harga Barang: ");
        scanf("%f", &new_barang.harga);

        FILE *fp = fopen(FILENAME, "a"); // Menggunakan fungsi append untuk menambahkan data ke baris paling terakhir jika file yang dituju ada
        if (fp == NULL)                  // Menggunakan null apabila file tidak ada
        {
            printf("Gagal membuka file.\n");
            return;
        }
        fprintf(fp, "%s %d %.2f\n", new_barang.nama, new_barang.jumlah, new_barang.harga); // Mencetak file yang sudah dimasukkan dengan fprintf (file print)
        fclose(fp);

        toko[jumlah_barang] = new_barang;
        jumlah_barang++;

        printf("Barang berhasil ditambahkan.\n");
    }
    else // Kondisi else apabila kondisi if tidak terpenuhi
    {
        printf("Maaf, toko sudah penuh.\n");
    }
}

void kurangi_barang() // Menambah fungsi dengan nama kurangi_barang
{
    if (jumlah_barang > 0) // Jika jumlah barang > 0 maka kondisi if akan berjalan
    {
        char nama_barang[50];

        printf("Nama Barang: ");
        scanf("%s", nama_barang);

        int i;
        int cari = 0;

        for (i = 0; i < jumlah_barang; i++)
        {
            if (strcmp(toko[i].nama, nama_barang) == 0) // Menggunakan strcmp untuk membandingkan karakter demi karakter, jika benar maka kode dilanjutkan
            {
                int jumlah_kurang;

                printf("Jumlah Kurang Barang: ");
                scanf("%d", &jumlah_kurang);

                if (jumlah_kurang <= toko[i].jumlah) // Kondisi if apabila jumlah_kurang < toko[i].jumlah yaitu struct
                {
                    toko[i].jumlah -= jumlah_kurang; // Maka data dari if jika benar akan dikurangi toko[i] -= jumlah_kurang

                    FILE *fp = fopen(FILENAME, "a"); // File yang dikurangi akan dibuka menggunakan fopen
                    if (fp == NULL)                  // Jika file tidak ada maka dia akan gagal dibuka
                    {
                        printf("Gagal membuka file.\n");
                        return;
                    }
                    fprintf(fp, "%s %d %.2f\n", toko[i].nama, toko[i].jumlah, toko[i].harga); // Melihat barang yang sudah dikurangi
                    fclose(fp);

                    printf("Barang berhasil dikurangi.\n");
                }
                else
                {
                    printf("Maaf, stok barang tidak mencukupi.\n");
                }

                cari = 1;
                break;
            }
        }

        if (!cari)
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
        printf("-----------------------------------------------------------------------\n");
        printf("| Nama Barang     | Jumlah Barang   | Harga Barang    | Total Harga   |\n");
        printf("-----------------------------------------------------------------------\n");
        printf("| %-15s | %15d | %15.2f | %13.2f |\n", nama, jumlah, harga, jumlah * harga);
        printf("-----------------------------------------------------------------------\n");
    }

    fclose(fp);
}

void pembayaran() // Membuat fungsi pembayaran
{
    if (jumlah_barang > 0) // Fungsi if dimana jika jumlah_barang > 0 maka kode akan berjalan
    {
        float total_harga = 0;
        for (int i = 0; i < jumlah_barang; i++)
        {
            total_harga += toko[i].jumlah * toko[i].harga; // Melakukan proses perhitungan pada total harga x jumlah barang
        }

        printf("Total Harga: %.2f\n", total_harga); // Mencetak total harga

        float jumlah_uang;
        printf("Jumlah Uang: ");
        scanf("%f", &jumlah_uang);

        if (jumlah_uang >= total_harga) // Fungsi if jika fungsi tersebut benar maka akan dijalankan
        {
            float kembalian = jumlah_uang - total_harga; // Melakukan proses perhitungan dengan jumlah_uang - total_harga
            printf("Kembalian: %.2f\n", kembalian);      // Sisa dari perhitungan
        }
        else
        {
            printf("Maaf, uang tidak mencukupi.\n");
        }
    }
    else // Fungsi else jika sudah tidak ada barang lagi
    {
        printf("Toko kosong.\n");
    }
}

int login() // Membuat fungsi login
{
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(USER_FILENAME, "r"); // Menggunakan file.txt dengan fungsi "r" yaitu read untuk membaca file
    if (fp == NULL)                       // Jika file tidak ada (null) maka akan menjalankan if
    {
        printf("Gagal membuka file.\n");
        return 0; // Login gagal
    }

    struct User user;
    while (fscanf(fp, "%s %s", user.username, user.password) == 2)
    {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) // Memakai strcmp untuk mengecek data yang sudah dibuat
        {
            fclose(fp);
            return 1; // Login berhasil
        }
    }

    fclose(fp);
    return 0; // Login gagal
}

void register_user() // Menggunakan fungsi register_user
{
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(USER_FILENAME, "a"); // Membuka file user_filename dan "a" akan dibuka untuk penambahan data di akhir file. Jika file tidak ada, maka file baru akan dibuat.
    if (fp == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);

    printf("Registrasi berhasil.\n");
}

int main() // Tempat menjalankan fungsi yang sudah dibuat
{
    printf("Selamat datang!\n");
    printf("1. Login\n");
    printf("2. Registrasi\n");
    printf("Pilihan: ");

    int pilih;
    scanf("%d", &pilih);

    switch (pilih)
    {
    case 1:
    {
        int masuk = login();

        if (masuk)
        {
            printf("Login berhasil!\n");

            // Simulasi loading progress bar
            int total = 100;
            struct timespec ts;
            ts.tv_sec = 0;
            ts.tv_nsec = 50000000L; // 50 milidetik

            for (int i = 0; i <= total; ++i)
            {
                printProgressBar(i, total);
                nanosleep(&ts, NULL); // Delay selama 50 milidetik
            }
            printf("\n");

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
                printf("1. Tambah Barang\n");
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
