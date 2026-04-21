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
 * run_external - forks, executes a command, and waits for it to finish
 * @the_path: full path of the executable command
 * @args: array of arguments passed to execve
 * @argv: shell argv (used for error messages)
 * @line_num: current command line number (used for error messages)
 * @line: original input line (freed on execve failure in child)
 *
 * Return: command exit status on success, 1 on fork failure, or 127 on execve
 * failure in the child process
 */

static int run_external(char *the_path, char **args, char **argv,
	int line_num, char *line)
{
	pid_t pid;
	int status = 0;

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
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], line_num, args[0]);
			free_exec(args, the_path);
			free(line);
			_exit(127);
		}
	}
	waitpid(pid, &status, 0);
	free_exec(args, the_path);
	return (WEXITSTATUS(status));
}

/**
 * exec_cmd - forks and executes a command
 * @line: the command to execute
 * @argv: pointer to argv[0] for error messages
 * @line_num: current line number for error messages
 *
 * @last_status: status of the previously executed command
 *
 * Return: exit status of the executed command
 */
int exec_cmd(char *line, char **argv, int line_num, int last_status)
{
	char **args = split_string(line, " \t");
	char *the_path;

	if (args == NULL || args[0] == NULL)
	{
		free_exec(args, NULL);
		return (0);
	}
	handle_builtin(args, line, last_status);

	the_path = pathfinder(args[0]);

	if (!the_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv[0], line_num, args[0]);
		free_exec(args, NULL);
		return (127);
	}
	return (run_external(the_path, args, argv, line_num, line));
}
