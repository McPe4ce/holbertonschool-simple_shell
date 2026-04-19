#include "simple_shell.h"

/**
 * main - Entry point for the simple shell program.
 * @argc: Argument count (not used).
 * @argv: Argument vector (used for error messages).
 * Return: Always 0 (success).
 */

int main(int argc, char **argv)
{
	size_t length = 0;
	char *line = NULL;
	int ret, last_status = 0;
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
		strip_newline(line);
		if (line[0] == '\0')
			continue;
		if (strcmp(line, "exit") == 0)
			break;
		ret = copy_idandexe(line, argv[0]);
		last_status = (ret == -1) ? 1 : ret;
	}
	free(line);
	return (last_status);
}
