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

/* shell.c */
void run_shell(char *prog_name);

/* helpers.c */
char *read_line(size_t *bufsize);
void exec_cmd(char *line, char **argv, int line_num);

/* myfunctions.c */
	void free_args(char **args);
	int _strlen(char *s);
	char *_strdup(char *s);
	char *_strcat_new(char *s1, char *s2);
	int _strcmp(char *s1, char *s2);

#endif
