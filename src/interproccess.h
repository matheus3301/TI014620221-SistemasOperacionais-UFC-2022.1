#ifndef INTERPROCCESS
#define INTERPROCCESS

void send_to_server(char *message, int socket_desc, struct sockaddr_in server_addr);

#endif