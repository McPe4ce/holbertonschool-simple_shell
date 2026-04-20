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
 *
 * Return: exit status of the executed command
 */
int exec_cmd(char *line, char **argv, int line_num)
{
	char **args = split_string(line, " \t");
	pid_t pid;
	int status = 0;
	char *the_path;

	if (args == NULL || args[0] == NULL)
	{
		free_exec(args, NULL);
		return (0);
	}
	the_path = pathfinder(args[0]);
	if (!the_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv[0], line_num, args[0]);
		free_exec(args, NULL);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_exec(args, the_path);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(the_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				argv[0], line_num, args[0]);
			free_exec(args, the_path);
			free(line);
			_exit(127);
		}
	}
	waitpid(pid, &status, 0);
	free_exec(args, the_path);
	return (WEXITSTATUS(status));
}
