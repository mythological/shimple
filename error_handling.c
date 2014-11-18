// throw these in the .h file

#include "error_handling.h"

pid_t
Fork()
{
	pid_t pid;
	
	if ( (pid = fork()) < 0 )
		error_handler(errno, "fork error");

	return pid;
}

void
error_handler(int code, char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(code));
	exit(1);
}
