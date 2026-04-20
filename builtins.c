#include "simple_shell.h"

/**
 * handle_builtin - The exit builtin is handled here and ends process
 * @args: arguments parsed
 * @line: the command to execute
 * @last_status: status of the previously executed command
 */
void handle_builtin(char **args, char *line, int last_status)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		free_exec(args, NULL);
		free(line);
		exit(last_status);
	}
}
