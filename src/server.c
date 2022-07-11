#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include "config.h"

int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr, client_addr;
    char client_message[2000];
    int client_struct_length = sizeof(client_addr);
    
    memset(client_message, '\0', sizeof(client_message));
    
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if(socket_desc < 0){
        printf("Error while creating socket\n");
        exit(EXIT_FAILURE);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    
    if(bind(socket_desc, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
        printf("Couldn't bind to the port\n");
        exit(EXIT_FAILURE);
    }
    
    while (1)
    {
        if (recvfrom(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr*) &client_addr, &client_struct_length) < 0)
        {
            printf("Couldn't receive\n");
            exit(EXIT_FAILURE);
        }
        printf("%s", client_message);
        fflush(stdout);
    }

    return 0;
}