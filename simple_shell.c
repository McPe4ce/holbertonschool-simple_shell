#include "simple_shell.h"

/**
 * copy_idandexe - Creates the child process and executes the command.
 * @command: Command given by the user in the terminal
 * Return: -1 on fork/wait error, exit status of child otherwise (127 if not found)
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
		_exit(127);
	}

	if (waitpid(pid, &status, 0) == -1)
		return (-1);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (-1);
}

/**
 * main - Simple shell entry point
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] used for error messages
 * Return: exit status of last executed command
 */

int main(int argc, char **argv)
{
	size_t length = 0;
	char *line = NULL;
	int null_checker, ret, last_status = 0;
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
			continue;
		if (strcmp(line, "exit") == 0)
			break;
		ret = copy_idandexe(line);
		if (ret == 127)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], line);
			last_status = 127;
		}
		else if (ret == -1)
		{
			perror("fork/wait");
			last_status = 1;
		}
		else
		{
			last_status = ret;
		}
	}
	free(line);
	return (last_status);
}
