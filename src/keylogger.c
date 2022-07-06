#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input-event-codes.h>

int main(void)
{
	struct input_event ev;
	int fd = open("/dev/input/event2", O_RDONLY);
	char map[] = "..1234567890-=..qwertyuiop{}..asdfghjkl;'...zxcvbnm,./... ";
	

	while (1)
	{
		int r = read(fd, &ev, sizeof(ev));
		if ((ev.type == EV_KEY) && (ev.value == 0))
		{
			if (ev.code == 28) printf("\n");
			if (ev.code == 14) printf("<=");
			else
			{
				printf("%c", map[ev.code]);
			}
			fflush(stdout);
		}
	}
	
	close(fd);
	return 0;
}