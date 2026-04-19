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

/**
 * main - Executes the shell, checks if we are in interactive to print prompt
 * gets the line of the input to analyse the command and replaces the new
 * line with NULL char before calling the func that executes process
 * Return: 0 (No errors)
 */

int main(void)
{
	size_t length = 0;
	char *line = NULL;
	int null_checker;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("($) ");
			fflush(stdout);
		}

		if (getline(&line, &length, stdin) == -1)
		{
			break;
		}
		for (null_checker = 0; line[null_checker] != '\0'; null_checker++)
		{
			if (line[null_checker] == '\n')
			{
				line[null_checker] = '\0';
				break;
			}
		}
		if (line[0] == '\0')
		{
			continue;
		}
		if (strcmp(line, "exit") == 0)
		{
			break;
		}
		if (copy_idandexe(line) == -1)
		{
			fprintf(stderr, "./elshellito: 1: %s: not found\n", line);
		}
	}
	free(line);
	printf("\n");
	return (0);
}
