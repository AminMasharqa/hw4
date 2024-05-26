#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 256
#define MAX_USERS 10
#define USER_FILE "users.txt"

typedef struct
{
    char username[10];
    char password[10];
} User;

typedef enum
{
    fail,
    success
} bool;

void register_user(const char *username, const char *password)
{
    FILE *file = fopen(USER_FILE, "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
}

int authenticate_user()
{
    char name[10];
    printf("Username: ");
    gets(name);

    int success_ = 0;
    char pass[10];
    printf("Password: ");
    gets(pass);

    // Print addresses for debugging
    printf("Address of pass: %p\n", (void *)pass);
    printf("Address of success_: %p\n", (void *)&success_);

    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return 0;
    }

    char file_username[10];
    char file_password[10];
    while (fscanf(file, "%s %s", file_username, file_password) != EOF)
    {
        if (strcmp(file_username, name) == 0 && strcmp(file_password, pass) == 0)
        {
            success_ = 1;
            break;
        }
    }
    fclose(file);

    printf("success_ at the end of the func : %d\n", success_);
    return success_;
}

void debug_show_users()
{
    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    char username[10];
    char password[10];
    int i = 0;
    while (fscanf(file, "%s %s", username, password) != EOF)
    {
        printf("User %d: %s, Password: %s\n", i, username, password);
        i++;
    }
    fclose(file);
}

void fill_users()
{
    register_user("user1", "password1");
    register_user("user2", "password2");
    register_user("user3", "password3");
    register_user("user4", "password4");
    register_user("user5", "password5");
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [register|authenticate|fill|show]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "register") == 0)
    {
        if (argc != 4)
        {
            printf("Usage: %s register <username> <password>\n", argv[0]);
            return 1;
        }
        register_user(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "authenticate") == 0)
    {
        if (authenticate_user())
        {
            printf("Authentication successful!\n");
        }
        else
        {
            printf("Authentication failed!\n");
        }
    }
    else if (strcmp(argv[1], "fill") == 0)
    {
        fill_users();
    }
    else if (strcmp(argv[1], "show") == 0)
    {
        debug_show_users();
    }
    else
    {
        printf("Unknown command: %s\n", argv[1]);
        printf("Usage: %s [register|authenticate|fill|show]\n", argv[0]);
        return 1;
    }

    return 0;
}
