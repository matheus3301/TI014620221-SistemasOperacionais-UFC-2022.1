#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *ptr;
    char *line;
    size_t sz_line;
    int flag = 0;

    ptr = fopen("/proc/bus/input/devices", "r");

    while (getline(&line, &sz_line, ptr) != -1)
    {
        if (strstr(line, "keyboard") != NULL) {
            getline(&line, &sz_line, ptr);
            getline(&line, &sz_line, ptr);
            break;
        }
    }
    char *ptr_event = strstr(line, "input/");
    if (ptr_event == NULL) printf("erro\n");
    else 
    {
        printf("%s", ptr_event + 6);
    }
    return 0;
}