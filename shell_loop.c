#include "simple_shell.h"

/**
 * run_shell - main shell loop: prompt, read, execute
 * @prog_name: argv[0], used in error messages
 */
void run_shell(char *prog_name)
{
	char *line = NULL;
	size_t bufsize = 0;
	int line_num = 0;

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
			exec_cmd(line, &prog_name, line_num);
	}
	free(line);
}
