#include "simple_shell.h"


int handle_builtin(char **args, char *line)
{
    if (_strcmp(args[0], "exit") == 0)
    {
        free_exec(args, NULL);
        free(line);
        exit(0);
    }
    return (0);
}