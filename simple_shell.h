/*
*simple_shell.h,
*This header regroups all the required prototypes and librairies needed,
*for the simple_shell project
*/

#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
int copy_idandexe(char *command);

#endif /*SIMPLE_SHELL_H*/
