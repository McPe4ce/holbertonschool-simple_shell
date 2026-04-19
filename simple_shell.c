#include "simple_shell.h"

/**
 * copy_idandexe - Creates the child process and executes the command.
 * @command: Command given by the user in the terminal
 * @the_shell: Name of the shell
 * Return: -1 on fork/wait error, exit status of child otherwise
 * (127 if not found)
 */

int copy_idandexe(char *command, char *the_shell)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();
	if (pid == -1)
	{
		return (-1);
	}

	if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;
		execve(command, argv, environ);
		fprintf(stderr, "%s: No such file or directory\n", the_shell);
		_exit(127);
	}
	else
	{
		wait(&status);
	}

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
	int null_checker, last_status = 0;
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
			{
				putchar('\n');
			}
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
		if (line[0] != '\0')
		{
			copy_idandexe(line, argv[0]);
		}
	}
	free(line);
	return (last_status);
}
