#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 256
#define MAX_USERS 10

typedef struct
{
    char username[10];
    char password[10];
} User;

User users[MAX_USERS];
int user_count = 0;

typedef enum
{
    fail,
    success
} bool;

void register_user(const char *username, const char *password)
{
    if (user_count < MAX_USERS)
    {
        strncpy(users[user_count].username, username, sizeof(users[user_count].username) - 1);
        strncpy(users[user_count].password, password, sizeof(users[user_count].password) - 1);
        user_count++;
    }
    else
    {
        printf("User limit reached.\n");
    }
}

bool authenticate_user(const char *username, const char *password)
{
    char buffer_auth[10]={0}; // Vulnerable buffer
    bool authenticate=fail;
    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            strcpy(buffer_auth, password); // Vulnerable to buffer overflow
            if (strcmp(users[i].password, buffer_auth) == 0)
            {
                authenticate =success;
            }
        }
    }
    return authenticate;
    
}

void debug_show_users()
{
    for (int i = 0; i < user_count; i++)
    {
        printf("User %d: %s, Password: %s\n", i, users[i].username, users[i].password);
    }
}

void fill_users()
{
    if (user_count + 5 <= MAX_USERS)
    {
        register_user("user1", "password1");
        register_user("user2", "password2");
        register_user("user3", "password3");
        register_user("user4", "password4");
        register_user("user5", "password5");
    }
    else
    {
        printf("Not enough space to add five users.\n");
    }
}

void handle_client(int newsockfd)
{
    char buffer[BUFFER_SIZE];
    int n;

    while ((n = read(newsockfd, buffer, BUFFER_SIZE - 1)) > 0)
    {
        buffer[n] = '\0';
        if (strncmp(buffer, "REGISTER ", 9) == 0)
        {
            char *username = strtok(buffer + 9, " ");
            char *password = strtok(NULL, " ");
            if (username && password)
            {
                register_user(username, password);
                write(newsockfd, "Registered successfully\n", 24);
            }
            else
            {
                write(newsockfd, "Invalid registration format\n", 28);
            }
        }
        else if (strncmp(buffer, "LOGIN ", 6) == 0)
        {

            char *username = strtok(buffer + 6, " ");
            char *password = strtok(NULL, " ");
            printf("%s",password);
            if (authenticate_user(username, password)==success)
            {
                write(newsockfd, "Login successful\n", 17);
            }
            else
            {
                write(newsockfd, "Login failed\n", 13);
            }
        }
        else if (strncmp(buffer, "DEBUG", 5) == 0)
        {
            debug_show_users();
        }
        else
        {
            write(newsockfd, "Unknown command\n", 16);
        }
        memset(buffer, 0, BUFFER_SIZE);
    }
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        perror("ERROR on accept");
        exit(1);
    }

    fill_users(); // Fill the array with five users

    handle_client(newsockfd);
    close(newsockfd);
    close(sockfd);
    return 0;
}
