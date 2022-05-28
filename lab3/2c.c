#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>

#define MAX_RECV_SIZE 1000


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("ERROR: Please input the correct net port\n");
        return -1;
    }
    const char *ip = argv[1];
    const short port = (short)atoi(argv[2]);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));  //每个字节都用0填充
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }
    if (connect(fd, (struct sockaddr*)(&addr), sizeof(addr)) == -1) {
        perror("connect");
        return 1;
    }

    printf("Please input your name:\n");
    char *username = NULL;
    size_t len = 0;
    getline(&username, &len, stdin);
    username[strlen(username) - 1] = '\0';
    printf("User [%s] has joined the room.\n", username);
    send(fd, username, len, 0);

    char me_info[100] = {};
    me_info[0] = '[';
    strcat(me_info, username);
    strcat(me_info, "(ME)]: ");


    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    else if (pid == 0) {
        // son
        while (1) {
            char *message = NULL;
                        
            size_t len = 0;
            getline(&message, &len, stdin);

            if (send(fd, message, len, 0) <= 0)
                break;
        }
    }
    else {
        // father
        while (1) {
            char buffer[1024] = {};
            if (recv(fd, buffer, MAX_RECV_SIZE, 0) <= 0) 
                break;
            printf("%s\n", buffer);
            
        }
    }

    close(fd);
    return 0;
}