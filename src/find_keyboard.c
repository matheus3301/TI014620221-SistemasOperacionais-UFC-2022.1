#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *ptr;
    char *line;
    char handlers[100];
    size_t sz_line;
    int flag = 0;

    ptr = fopen("/proc/bus/input/devices", "r");

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
        for (char *p = ev_ptr; *p != ' '; p++)
        {
            printf("%c", *p);
        }
        printf("\n");
    }
    return 0;
}