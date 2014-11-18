#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "shell_functions.h"


int
main()
{
	char *cmdline;
	cmdline = NULL;

	while (1) {

		cmdline = readline("> ");
		if (feof(stdin)) {
			exit(0);
		}

		eval(cmdline);
		free(cmdline);
	}
}
