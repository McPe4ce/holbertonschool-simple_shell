#include "simple_shell.h"

/**
 * copy_idandexe - Creates the child process and execute the process
 * if found while telling parent to wait.
 * @command: Command given by the user in the terminal
 * Return: -1 (Error), 1 (Successfully executed program)
 */

int copy_idandexe(char *command)
{
	pid_t pid;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;
	pid = fork();

	if (pid == -1)
	{
		return (-1);
	}

	if (pid == 0)
	{
		execve(command, argv, environ);
		perror("Error");
		exit(127);
	}
	else
	{
		if (wait(NULL) == -1)
		{
			perror("wait");
			return (-1);
		}
	}
	return (1);
}
