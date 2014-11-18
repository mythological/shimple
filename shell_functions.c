#include "shell_functions.h"
extern char  **environ;

#define MAXARGS 128

void
eval(char *cmdline)
{
	size_t buflen = strlen(cmdline) + 1;
	char  *argv[MAXARGS];
	char   buf[buflen];
	int    backGrond;
	pid_t  pid;

	strcpy(buf, cmdline);
	buf[buflen-1] = ' ';
	buf[buflen]   = '\0';
	backGrond     = parseline(buf, argv);
	
	// return if line is empty
	if (argv[0] == NULL)
		return;

	if ( !builtin_command(argv) ) {

		if ( (pid = Fork()) == 0 ) {
			if (execvp(argv[0], argv) < 0) {

				error_handler(errno, "wtf is this");
				exit(0);
			}
		}
		
		// if foreground process, then wait until it terminates
		if (!backGrond) {

			int status;
			if ( waitpid(pid, &status, 0) < 0) {

				error_handler(errno, "wait foreground: waitpid error");
			}
		}
		else {
	
			printf("%d %s", pid, cmdline);
		}
		return;
	}	
} 

int
builtin_command(char **argv)
{
	if ( !strcmp(argv[0], "exit") ) {

		exit(0);
	}
	else if ( !strcmp(argv[0], "cd") ) { 

		cd(argv);
		return 1;
	}
	else if ( !strcmp(argv[0], "&") ) {

		return 1;
	}
	return 0;
}

int
parseline(char *buf, char **argv)
{
	int backGrond;
	int argc;
	char *delim;
	
	backGrond = argc = 0;
	delim = NULL;

	// replace trailing newlines with spaces
	buf[strlen(buf)-1] = ' ';
	
	// ignore leading spaces
	while (*buf && (*buf == ' '))
		buf++;

	// build the list of arguments
	argc = 0;
	while ( (delim = strchr(buf, ' ')) ) {

		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' '))
			buf++;
	}

	// NULL terminate the string
	argv[argc] = NULL;

	// if the line is blank, we return 1
	if (argc == 0)
		return 1;

	// check whether job should run in foreground or background
	if ( (backGrond = (*argv[argc-1]) == '&') != 0)
		argv[--argc] = NULL;
	
	return backGrond;
}

void
cd(char **argv)
{
	if (argv[0] == NULL)
		return;
	if (argv[1] == NULL)
		chdir(getenv("HOME"));
	else {
		chdir(argv[1]);
	}
}
