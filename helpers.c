#include "simple_shell.h"

/**
 * read_line - reads one line from stdin
 * @bufsize: pointer to buffer size (managed by getline)
 *
 * Return: pointer to line, or NULL on EOF
 */
char *read_line(size_t *bufsize)
{
	char *line = NULL;
	ssize_t nread;

	nread = getline(&line, bufsize, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	return (line);
}

/**
 * exec_cmd - forks and executes a command
 * @line: the command to execute
 * @argv: pointer to argv[0] for error messages
 * @line_num: current line number for error messages
 */
void exec_cmd(char *line, char **argv, int line_num)
{
	char *args[2];
	pid_t pid;
	int status;

	args[0] = line;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (execve(line, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], line_num, line);
				free(line);
			_exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
