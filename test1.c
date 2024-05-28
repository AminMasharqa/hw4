#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_LENGTH 8
#define USERNAME_SIZE 40
#define PASSWORD_SIZE 40
#define FILENAME "users.txt"

char PASSWORD[10] = "amin123";

// Signal handler for SIGSEGV
void sigsegv_handler(int signum) {
    printf("Caught segmentation fault (SIGSEGV). Signal number: %d\n", signum);
    // Perform cleanup or logging here
    exit(1);
}

void debug_show_all_passwords() {
    char file_username[USERNAME_SIZE];
    char file_password[PASSWORD_SIZE];

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Registered users and passwords:\n");
    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
        printf("Username: %s, Password: %s\n", file_username, file_password);
    }

    fclose(file);

}

bool login() {
    char file_username[USERNAME_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    char file_password[PASSWORD_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    char username[USERNAME_SIZE] = {5, 5, 5, 5, 5, 5};
    bool authenticated = false;
    char password[PASSWORD_SIZE] = {6, 6, 6, 6, 6, 6};

    printf("Enter username: ");
    gets(username);  // Unsafe function, susceptible to buffer overflow

    printf("Enter password: ");
    gets(password);  // Unsafe function, susceptible to buffer overflow

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            authenticated = true;
            break;
        }
    }

    fclose(file);
    return authenticated;
}

int main() {
    // Set up signal handler for SIGSEGV
    signal(SIGSEGV, sigsegv_handler);

    if (login() == true)
        printf("\nyou are authenticated!\n");
    else
        printf("\nyou are not authenticated!\n");


    // if (login() == true)
    //     debug_show_all_passwords();


    return 0;
}
