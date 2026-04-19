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
	int start, end, i;

	nread = getline(&line, bufsize, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	if (line[nread - 1] == '\n')
		line[--nread] = '\0';
	start = 0;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	end = nread;
	while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t'))
		end--;
	line[end] = '\0';
	i = 0;
	while (start < end)
		line[i++] = line[start++];
	line[i] = '\0';
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
	char **args = split_string(line, " \t");
	pid_t pid;
	int status;

	if (argv == NULL || argv[0] == NULL)
	{
		free_args(args);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_args(args);
		return;
	}
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], line_num, line);
			free_args(args);
			free(line);
			_exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free_args(args);
	}
}
