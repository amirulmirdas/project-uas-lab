#define USER_FILENAME "data_user.txt"
// struct akun
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
    return 0; // Login gagal
}