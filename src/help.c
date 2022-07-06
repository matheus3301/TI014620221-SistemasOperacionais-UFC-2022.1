#include "help.h"
#include <stdio.h>
#include <stdlib.h>

void show_help_and_exit()
{
    fprintf(stderr, "\
            [usage]        <options>\n\
            -server        server to send all data.\n\
            -file          local file to store all events.\n");
    exit(-1);
}