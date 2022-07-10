#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "interproccess.h"

void send_to_server(char *message, int socket_desc, struct sockaddr_in server_addr)
{
    int server_struct_length = sizeof(server_addr);
    if (sendto(socket_desc, message, strlen(message), 0, (struct sockaddr *)&server_addr, server_struct_length) < 0)
    {
        printf("error: unable to send message to external server\n");
    }
}
