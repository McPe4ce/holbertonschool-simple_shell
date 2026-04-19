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
	int status;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		execve(command, argv, environ);
		_exit(127); /* execve a échoué */
	}

	if (waitpid(pid, &status, 0) == -1)
		return (-1);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (-1);
}

/**
 * main - Executes the shell, checks if we are in interactive to print prompt
 * gets the line of the input to analyse the command and replaces the new
 * line with NULL char before calling the func that executes process
 * Return: 0 (No errors)
 */

int main(int argc, char **argv)
{
	size_t length = 0;
	char *line = NULL;
	int null_checker, ret;
	ssize_t stored_line;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("($) ");
			fflush(stdout);
		}
		stored_line = getline(&line, &length, stdin);
		if (stored_line == -1)
		{
			if (ferror(stdin))
			{
				perror("getline");
				free(line);
				return (1);
			}
			if (isatty(STDIN_FILENO))
				putchar('\n');
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
		ret = copy_idandexe(line);
		if (ret == 127)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], line);
		}
		else if (ret == -1)
		{
		perror("fork/wait");
		}
	}
	free(line);
	return (0);
}
