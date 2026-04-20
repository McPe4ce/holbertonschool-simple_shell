#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*
*simple_shell.h,
*This header regroups all the required prototypes and librairies needed,
*for the simple_shell project
*/

extern char **environ;

/* shell.c */
int run_shell(char *prog_name);

/* helpers.c */
char *read_line(size_t *bufsize);
int exec_cmd(char *line, char **argv, int line_num, int last_status);

/* String spliter*/
char **split_string(const char *str, const char *delimiters);

/* myfunctions.c */
void free_exec(char **args, char *the_path);
int _strlen(char *s);
char *_strdup(char *s);
char *_strcat_new(char *s1, char *s2);
int _strcmp(char *s1, char *s2);

/* PATH.c */
char *_getenv(const char *name);
char *pathfinder(char *cmd);

/*builtins.c*/
void handle_builtin(char **args, char *line, int last_status);
int handle_env(void);

#endif
