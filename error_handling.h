#ifndef __SHIMPLE_ERROR__
#define __SHIMPLE_ERROR__
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void error_handler(int code, char *msg);
pid_t Fork(void);

#endif
