#ifndef __SHIMPLE_SF__
#define __SHIMPLE_SF__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "error_handling.h"

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void cd(char **argv);

#endif
