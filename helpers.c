#include "simple_shell.h"

/**
 * copy_idandexe - Fork and execve a command.
 * @command: command to execute
 * @the_shell: argv[0] for error messages
 * Return: -1 on fork/wait error, child exit status otherwise
 */

int copy_idandexe(char *command, char *the_shell)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;
		execve(command, argv, environ);
		fprintf(stderr, "%s: 1: %s: not found\n", the_shell, command);
		_exit(127);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

/**
 * strip_newline - Replace trailing newline in line with '\0'.
 * @line: line read from getline
 */
void strip_newline(char *line)
{
	int i;

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return;
		}
	}
}
