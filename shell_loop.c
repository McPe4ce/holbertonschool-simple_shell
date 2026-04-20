#include "simple_shell.h"

/**
 * run_shell - main shell loop: prompt, read, execute
 * @prog_name: argv[0], used in error messages
 *
 * Return: exit status of the last command executed
 */
int run_shell(char *prog_name)
{
	char *line = NULL;
	size_t bufsize = 0;
	int line_num = 0;
	int last_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_line(&bufsize);
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line_num++;
		if (line[0] != '\0')
		{
			last_status = exec_cmd(line, &prog_name, line_num, last_status);
		}
		free(line);
		line = NULL;
	}
	free(line);
	return (last_status);
}
