#include "simple_shell.h"

/**
 * main - entry point
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: 0
 */

int main(int argc, char **argv)
{
	(void)argc;
	run_shell(argv[0]);
	return (0);
}
