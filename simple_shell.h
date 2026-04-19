#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
*simple_shell.h,
*This header regroups all the required prototypes and librairies needed,
*for the simple_shell project
*/

extern char **environ;
int copy_idandexe(char *command, char *the_shell);
void strip_newline(char *line);

#endif
