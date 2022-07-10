#ifndef KEYLOGGER
#define KEYLOGGER
#include <stdio.h>

char *find_keyboard();
void capture_keys(FILE *file, char *event);

#endif