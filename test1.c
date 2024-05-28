// alamin masharqa 207358326            adan fadila 314705062 

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_LENGTH 8
 
#define FILENAME "users.txt"


void debug_show_all_passwords() {
    char file_username[MAX_LENGTH];
    char file_password[MAX_LENGTH];

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Registered users and passwords:\n");
    while (fscanf(file, "%s", file_username ) != EOF) {
        fscanf(file, "%s", file_username);
        printf("Username: %s", file_username);
        
    }

    fclose(file);

}

bool login() {

    volatile bool authenticated = false;
    char password[MAX_LENGTH] = {6, 6, 6, 6, 6, 6,6};
    char username[MAX_LENGTH] = {5, 5, 5, 5, 5, 5,5};
    char file_username[MAX_LENGTH] = {1, 2, 3, 4, 5, 6, 7};
    char file_password[MAX_LENGTH] = {1, 2, 3, 4, 5, 6, 7};

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

int main(int argc, char const *argv[])
{
    if(login()!= false)
        printf("YOU ARE AUTHENTICATED !\n");
    else
        printf("YOU ARE not AUTHENTICATED !\n");

    

    return 0;
}

