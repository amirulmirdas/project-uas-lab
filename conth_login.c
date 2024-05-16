#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USER_FILENAME "data_user.txt"

// Struct pengguna
struct User
{
    char username[50];
    char password[50];
};

// Fungsi Login 
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

// Fungsi Register
void registerUser()
{
    char username[50];
    char password[50];
    printf("Mari bergabung dengan teman jual akun game online kami!\n");
    printf("Buat username baru: ");
    scanf("%s", username);

    printf("Buat password baru: ");
    scanf("%s", password);

    FILE *fp = fopen(USER_FILENAME, "a");
    if (fp == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);
    printf("Registrasi berhasil! Selamat bergabung!\n");
}

int main() {
    int choice;
    printf("Selamat datang di Teman Jual Akun Game Online!\n");
    printf("\nMenu:\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("Pilihan: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        if (login())
            printf("Selamat datang kembali! Anda berhasil login.\n");
        else
            printf("Login gagal. Silahkan coba lagi.\n");
        break;
    case 2:
        registerUser();
        break;
    default:
        printf("Pilihan tidak valid.\n");
        break;
    }

    printf("Tekan tombol enter untuk melanjutkan...");
    while (getchar() != '\n'); // Membersihkan buffer input
    getchar();
    system("cls"); // Membersihkan layar di Windows
    // system("clear"); // Membersihkan layar di Linux/MacOS

    return 0;
}