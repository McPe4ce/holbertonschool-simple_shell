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
	ssize_t char_numb;
	int start = 0, end, index = 0;

	char_numb = getline(&line, bufsize, stdin);
	if (char_numb == -1)
	{
		free(line);
		return (NULL);
	}
	if (line[char_numb - 1] == '\n')
	{
		line[--char_numb] = '\0';
	}
	while (line[start] == ' ' || line[start] == '\t')
	{
		start++;
	}
	end = char_numb;
	while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t'))
	{
		end--;
	}
	line[end] = '\0';

	while (start < end)
	{
		line[index++] = line[start++];
	}
	line[index] = '\0';
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
